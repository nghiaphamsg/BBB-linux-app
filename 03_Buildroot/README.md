<h2> How To Using Buildroot For Generate U-boot & RFS </h2>

### Step 1: Download source and extract file
I'm using version buildroot-2017.05
```shell
https://buildroot.org/downloads/
```
```shell
tar xfv buildroot-2017.05.tar.gz
```

### Step 2: Clean all the previously compiled/generated object files
```shell
make distclean
```

### Step 3: Apply board default configuration
```shell
make beaglebone_config
```

### Step 4:  If you want to do any settings other than default configuration
```shell
make menuconfig
```
You can refer to how I configure the following:

- 1.Target option (not configure)
- 2.Build option (not configure)
- 3.Toolchain:
  + Toolchain: Linaro 6.4.1
  ![Screenshot from 2020-09-02 22-00-49](https://user-images.githubusercontent.com/32474027/91988808-ae9c0c00-ed6a-11ea-88d0-1da612db1305.png)
  
- 4.System configuration:
  ![Screenshot from 2020-09-02 22-01-33](https://user-images.githubusercontent.com/32474027/91988848-bc519180-ed6a-11ea-9e53-fd60f6e59094.png)
  
- 5.Kernel:
  + Defconfig name (v4.11.3) → omap2plus
  + Loadaddress: 0x80008000
  + Device tree source: am335x-boneblack
  ![Screenshot from 2020-09-02 22-01-50](https://user-images.githubusercontent.com/32474027/91988890-cecbcb00-ed6a-11ea-95f1-735729d01468.png)
  
- 6.Target packages: (you can enable function if you need, Ex: ssh (openssh),..)
- 7.Filesystem images (not configure)
- 8.Bootloaders:
  + Build system: Kconfig
  + U-boot version: 2017.03
  + Board defconfig: am335x_boneblack
  ![Screenshot from 2020-09-02 22-02-19](https://user-images.githubusercontent.com/32474027/91989596-a4c6d880-ed6b-11ea-8615-2f49c3ce0b72.png)

- 9.Host utilities (not configure)
- 10.Legacy config options (not configure)

### Step 5: Generate (about 15~20 min)
```shell
make -j4
```
**Note:** j4 (4 core machine) will instructs the make tool to spawn 4 threads\
You can find number of cores your CPU have
```shell
cat /proc/cpuinfo | grep processor | wc -l
```
 After generated, move to `/output/images`
 
 ![Screenshot from 2020-09-02 21-59-42](https://user-images.githubusercontent.com/32474027/91990120-5108bf00-ed6c-11ea-9ca4-d6b023c21e68.png)

### Step 6: Copy file into SD card or anything can boot
```shell
sudo cp uImage u-boot.img amx335x-boneblack.dtb MLO /media/neko/BOOT
sudo tar -xf rootfs.tar -C /media/neko/ROOTFS
```

