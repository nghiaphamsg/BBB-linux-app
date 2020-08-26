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
- Copy "MLO" or "SPL" into the internal SRAM of the chip
- Execute "MLO" or "SPL"\
**Note**: The Public ROM Code is physically located at the address 20000h.

![Screenshot from 2020-08-26 20-52-38](https://user-images.githubusercontent.com/32474027/91300395-2a7fdc80-e7de-11ea-9af3-276574e17fab.png)

### 2. Booting
- First a booting device list is created. The list consists of all devices which will be searched for a booting image. The list is filled in based on the SYSBOOT.

![Screenshot from 2020-08-26 20-56-00](https://user-images.githubusercontent.com/32474027/91300639-95c9ae80-e7de-11ea-8490-d12c0541fbc7.png)

## Phase 2 MLO/SPL
- Print out console the debug message
- Reconfigures the PLL to desired value
- Initializes the DDR registers to use the DDR memory
- Does muxing configurations of boot peripherals pin
- Copies the u-boot image into the DDR memory and passes control to it
![Screenshot from 2020-08-26 21-27-32](https://user-images.githubusercontent.com/32474027/91303702-58b3eb00-e7e3-11ea-960a-15193db0316a.png)

## Phase 3 U-Boot
- Initialize some of the peropherals like I2C, NAND, FLASH, ETHERNET, UART, USB, MMC,..etc. Because it supports loading kernel from all these peripherals
- Load the Linux kernel image form various boot sources to the DDR memory of the board
- Boot sources: USB, eMMC, SD card, Ethernet, serial port, NAND, Flash,etc.
- Passing of boot arguments to the kernel
- Change the boot behavior of the u-boot by using a file called uEnv.txt\
For example:
  ```text
    console=ttyO0,115200n8
    ipaddr=192.168.7.2
    serverip=192.168.7.1
    loadaddr=0x82000000         // DDR address
    fdtaddr=0x88000000
    loadfromsd=load mmc 0:2 ${loadaddr} /boot/uImage;load mmc 0:2 ${fdtaddr} /boot/am335x-boneblack.dtb
    linuxbootargs=setenv bootargs console=${console} root=/dev/mmcblk0p2 rw 
    uenvcmd=setenv autoload no; run loadfromsd; run linuxbootargs; bootm ${loadaddr} - ${fdtaddr}
  ```
## Phase 4 Linux Kernel
**Location on memory**
![Screenshot from 2020-08-26 23-35-39](https://user-images.githubusercontent.com/32474027/91317377-f06e0500-e7f4-11ea-9e84-0fda18544698.png)

**Linux boot sequence**
![Screenshot from 2020-08-26 23-40-26](https://user-images.githubusercontent.com/32474027/91317897-915cc000-e7f5-11ea-98db-108d8835a805.png)

--------------------------------------------------------------------------------------------------------------------------------------------
### AMX335x Boot Sequence
![Screenshot from 2020-08-27 00-36-15](https://user-images.githubusercontent.com/32474027/91324943-9b82bc80-e7fd-11ea-9ba2-df2e681b6689.png)

