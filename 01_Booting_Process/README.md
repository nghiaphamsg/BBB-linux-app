<h1> Start-up and Configuration <h1>

## Stage Boot of BBB
![Screenshot from 2020-08-26 21-08-40](https://user-images.githubusercontent.com/32474027/91302062-d7f3ef80-e7e0-11ea-9b73-5ed2fa21825a.png)

**Note:**
- RBL (ROM BootLoader): load and execute the second stage bootloader from internal memory of SoC
- SPL/MLO (Second Program Loader/Memory Loader): load and execute the third stage bootloader from DDR
- U-Boot (Third stage bootloader): load and execute the Linux Kernel from DDR
- MMC0: SD Card
- MMC1: eMMC
- SRAM: internal (built-in) RAM
- DDR: external RAM (2 signals/1 clock cycle)

## Phase 1 RBL
### 1. ROM Code Start-up
- Stack setup
- Watchdog timer 1 configuration (set to 3 min timeout)
- System clock configuration using PLL
![Screenshot from 2020-08-26 20-54-30](https://user-images.githubusercontent.com/32474027/91301577-1dfc8380-e7e0-11ea-8ad2-2376929fcd97.png)
- Search Memory devices or other bootable interface for MLO or SPL
- Copy [MLO/SPL](https://github.com/nghiaphamsg/BeagleboneBlack_Debian/tree/master/Generate_MLO_RFS/Genenal) into the internal SRAM of the chip
- Execute "MLO" or "SPL"\
**Note**: The Public ROM Code is physically located at the address 20000h.

![Screenshot from 2020-08-26 20-52-38](https://user-images.githubusercontent.com/32474027/91300395-2a7fdc80-e7de-11ea-9af3-276574e17fab.png)

### 2. Booting
- First a booting device list is created. The list consists of all devices which will be searched for a booting image. The list is filled in based on the SYSBOOT.

![Screenshot from 2020-08-26 20-56-00](https://user-images.githubusercontent.com/32474027/91300639-95c9ae80-e7de-11ea-8490-d12c0541fbc7.png)

## Phase 2 MLO/SPL
- Print out console the debug message.
- Reconfigures the PLL to desired value.
- Initializes the DDR registers to use the DDR memory.
- Does muxing configurations of boot peripherals pin.
- Copies the [u-boot.img](https://github.com/nghiaphamsg/BeagleboneBlack_Debian/tree/master/Generate_MLO_RFS/Genenal) into the DDR memory and passes control to it
![Screenshot from 2020-08-30 17-52-16](https://user-images.githubusercontent.com/32474027/91655189-e5172400-eae9-11ea-8af4-ec693a7a5425.png)

## Phase 3 U-Boot
- Initialize some of the peropherals like I2C, NAND, FLASH, ETHERNET, UART, USB, MMC,..etc. Because it supports loading kernel from all these peripherals.
- Load the Linux kernel image form various boot sources to the DDR memory of the board (Boot sources: USB, eMMC, SD card, ethernet, serial port, NAND, flash,etc).
- Passing of boot arguments to the kernel.\
- Change the boot behavior of the u-boot by using a file called [uEnv.txt](https://github.com/nghiaphamsg/BeagleboneBlack_Debian/blob/master/Generate_MLO_RFS/Genenal/uEnv.txt)

#### Show detail
**Step 1:** u-boot.img looking for [uImage](https://github.com/nghiaphamsg/BeagleboneBlack_Debian/tree/master/Generate_MLO_RFS/Genenal) (Kernel image), uImage is nothing but zImage plus u-boot header

  ![Screenshot from 2020-08-30 17-57-48](https://user-images.githubusercontent.com/32474027/91655261-5a82f480-eaea-11ea-839d-cef48d6a2011.png)

**Step 2:** Reading u-boot header (64bytes) of the uImage manually (dump header)
```shell
  cd u-boot/include; vi +307 image.h
```
```text
    typedef struct image_header {
        uint32_t ih_magic;          /* Image Header Magic Number */
        uint32_t ih_hcrc;           /* Image Header CRC Checksum */
        uint32_t ih_time;           /* Image Creation Timestamp */
        uint32_t ih_size;           /* Image Data Size */
        uint32_t ih_load;           /* Data Load Address */
        uint32_t ih_ep;             /* Entry Point Address */
        uint32_t ih_dcrc;           /* Image Data CRC Checksum */
        uint8_t ih_os;              /* Operating System */
        uint8_t ih_arch;            /* CPU architecture */
        uint8_t ih_type;            /* Image Type */
        uint8_t ih_comp;            /* Compression Type */
        uint8_t ih_name[IH_NMLEN];  /* Image Name */
    } image_header_t;
```

- How to dump memory in U-Boot stage:
    + Step 1: Press space bar after when you power on

    + Step 2: Load uImage in to the DDR address (0x8200_0000)\
`=> load mmc 0:1 0x82000000 uImage`
```text
    reading uImage
    8957456 bytes read in 563 ms (15.2 MiB/s)
```

   + Step 3: Use "md" commad to show memory infomation\
`=> md 0x82000000 10`
```text
    82000000: 56190527 4ef60b6b a920495f d0ad8800    '..Vk..N_I .....
    82000010: 00800080 00800080 39386b9d 00020205    .........k89....
    82000020: 756e694c 2e342d78 35312e34 00000035    Linux-4.4.155...
    82000030: 00000000 00000000 00000000 00000000    ................
```
Or use "imi" commad such as:\
`=> imi 0x82000000`
```text
    ## Checking Image at 82000000 ...
      Legacy image found
      Image Name:   Linux-4.4.155
      Created:      2020-08-28  15:20:09 UTC
      Image Type:   ARM Linux Kernel Image (uncompressed)
      Data Size:    8957392 Bytes = 8.5 MiB
      Load Address: 80008000
      Entry Point:  80008000
      Verifying Checksum ... OK
```

**Step 3:** How U-boot hands off control to the Boot Strap Loader of the Linux kernel
- Let's go to the "bootm.c" file of the U-Boot source code and Explore
```shell
  cd u-boot-2017.05-rc2/arch/arm/lib/bootm.c
```
- In the boot_jump_linux(): this function pointer is initialized to entry point address\
`kernel_entry = (void (*)(int, int, uint))images->ep;`
- And this code hand off control to the Linux\
`kernel_entry(0, machid, r2);`\
  it actually sends three important arguments:
    + 0: it actually ignored by the Linux.
    + machid: machine id of the board which is detected by the u-boot, passed to linux via r1.
    + r2: address of DTB (FTB) present in the DDR RAM
      
**Location on memory**
  ![Screenshot from 2020-08-30 22-53-39](https://user-images.githubusercontent.com/32474027/91661591-f7a85200-eb17-11ea-8da6-d3422c25198b.png)
  **Note**
  - Load address (download address): this is the address in memory space where you download the uImage file
  to the first address of the uImage file in the system memory (RAM or parallel NOR flash,..etc). 
  - A modern U-Boot, for TI platforms such as the Beaglebone Black will have a default environment that uses 
  addresses based on that document. Looking at the [code](https://elixir.bootlin.com/u-boot/latest/source/include/configs/ti_armv7_common.h#L33) in U-Boot we see that the uImage is loaded to 0x82000000 and the device tree to 0x88000000.

## Phase 4 Linux Boot

**Linux boot sequence**
![Screenshot from 2020-08-26 23-40-26](https://user-images.githubusercontent.com/32474027/91665525-31398700-eb31-11ea-8bd8-ab3180f6ef5d.png)

#### Step 1: Start routine stage
```shell
  cd /linux-4.4/arch/arm/boot/compressed; vi head.S
```
  + Write machine ID (r1) into the r7 register
  + Write dtb/ftb address (r2) in to the r8 register

![Screenshot from 2020-08-31 00-26-58](https://user-images.githubusercontent.com/32474027/91663009-0e9f7200-eb21-11ea-9b45-c6b334b4648d.png)

#### Step 2: Decompression of the compressed kernel happens in misc.c
  - Search "decompress_kernel" in head.S
```vim
  :/decompress_kernel
```
  - It actually call decompress_kernel() in misc.c 
```vim
  cd /linux-4.4/arch/arm/boot/compressed; vi misc.c
```

![Screenshot from 2020-08-31 00-51-36](https://user-images.githubusercontent.com/32474027/91663573-b4081500-eb24-11ea-8a04-9fa51c10c103.png)

#### Step 3: Kernel start entry point
```shell
  cd /linux-4.4/arch/arm/kernel/; vi head.S
```
- head.S is actually architecture specific code. It's not depending upon any SOC family. It's a generic startup code for arm processors.
  + 1. CPU specific initializations
  + 2. Check for valid processor architecture
  + 3. Page table inits
  + 4. Initialize and prepare MMU for the indentified processor architecture
  + 5. Enable MMU to support virtual memory
  + 6. Calls "start_kernel" function of the main.c ("Arch" independent code)
- Kernel start from entry point address:
![Screenshot from 2020-08-31 01-17-36](https://user-images.githubusercontent.com/32474027/91664115-144c8600-eb28-11ea-9aa9-c0df78184d34.png)

- After that turn on MMU:
![Screenshot from 2020-08-31 01-22-02](https://user-images.githubusercontent.com/32474027/91664193-90df6480-eb28-11ea-9637-3b3b1d9e8ae2.png)

#### Step 4: Function called start kernel in head-common.S
```shell
  cd /linux-4.4/arch/arm/kernel/; vi head-common.S
```
![Screenshot from 2020-08-31 01-26-56](https://user-images.githubusercontent.com/32474027/91664323-5de9a080-eb29-11ea-91c1-5743be0120cb.png)

#### Step 5&6: The flow control comes to the file main.c of the Linux kernel
```shell
  cd /linux-4.4/init; vi main.c
```
- 1.main.c#L:499 
  + start_kernel() code does all the startup work for the Linux kernel from initializing the very first kernel thread.
  + All the way to mounting a root file system and executing the very first user space Linux application program.

- 2.rest_init()#L:387
  + creating 2 kernel threads by call kernel_thread():
     + one is called kernel_init which pid number 1.
     + create another one is called kthreadd (used to spawn other kernel threads) which pid number 2
  + init_idle_bootup_task(current): starting the scheduler and then kernel is going to CPU idle loop.
  
- 3.kernel_init()#L:933
     + free_initmem(): the memory consumed by initialization functions so far will be reclaimed, because those functions are no longer needed and no one going to call them.
     + try_to_run_init_process(): Try to run the init application
![Screenshot from 2020-08-31 02-11-39](https://user-images.githubusercontent.com/32474027/91665288-6f35ab80-eb2f-11ea-8cc4-08c80b0d9d03.png)

## Booting Process Log

![Screenshot from 2020-08-30 18-22-44](https://user-images.githubusercontent.com/32474027/91665568-81184e00-eb31-11ea-8d07-b72809d02f33.png)


--------------------------------------------------------------------------------------------------------------------------------------------
### AMX335x Boot Sequence
![Screenshot from 2020-08-27 00-36-15](https://user-images.githubusercontent.com/32474027/91324943-9b82bc80-e7fd-11ea-9ba2-df2e681b6689.png)

