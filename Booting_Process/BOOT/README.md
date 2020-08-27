<h1> The First Stage: Discuss About U-boot Source</h1>

### Step 1: Download U-boot source code
```text
  ftp://ftp.denx.de/pub/u-boot/
```

### Step 2: Extract file and discuss about the U-boot architecture
```shell
  tar -xf u-boot-2017.05-rc2.tar.bz2
```
- Different processor architecture produced by ARM
```text
arch
├── arm
    ├── cpu
        ├── arm11
        ├── arm1136
        ├── arm1176
        ├── arm720t
        ├── arm920t
        ├── arm926ejs
        ├── arm946es
        ├── armv7
        ├── armv7m
        ├── armv8
        ├── pxa
        └── sa1100
```
- U-boot supports various boards such as TI with AM355x
```text
board
├── ti
    ├── am335x
    ├── am3517crane
    ├── am43xx
    ├── am57xx
    ├── am65x
    ├── beagle
    ├── common
    ├── dra7xx
    ├── evm
    ├── j721e
    ├── ks2_evm
    ├── omap5_uevm
    ├── panda
    ├── sdp4430
    └── ti816x
```
- And default configuration is used when you have no idea how to configure the U-Boot source code.
  It is guaranteed that the basic and the required functionalities
```text
 /configs/am335x_boneblack_defconfig
````

-----------------------------

<h1> The Second Stage: How To Create MLO/SPL, u-boot.img,..etc </h1>

## Cross toolchain compile install (skip if you using Ubuntu, Debian,..)

If you want to use toolchain from source file
### Step 1: Download arm cross toolchain
```text
  https://releases.linaro.org/components/toolchain/binaries/6.3-2017.02/arm-linux-gnueabihf/
```
### Step 2: Export path of the cross compilation toolchain
```shell 
  export PATH=$PATH:/<include_path>/6.3-2017.02/arm-linux-gnueabihf/bin
```
or install by command
```shell
  sudo apt-get install arm-linux-gnueabihf-*
```


## U-Boot compilation

### Step 1: Delete all the previously compiled/generated object files
```shell
  make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- distclean
```

### Step 2: Apply board default configuration for uboot
```shell
  make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- am335x_boneblack_defconfig
```

### Step 3: If you want to do any settings other than defaul configuration
```shell
  make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- menuconfig
```

### Step 4: Compile
   You can find number of cores your CPU have
```shell
  cat /proc/cpuinfo | grep processor | wc -l
```

```shell
  make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -j4

  make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -j8
```
- j4 (4 core machine) will instructs the make tool to spawn 4 threads
- j8 (8 core machine) will instructs the make tool to spawn 8 threads
![Screenshot from 2020-08-27 23-10-06](https://user-images.githubusercontent.com/32474027/91456152-e6640900-e8bd-11ea-9c79-ace5e37ef8bb.png)

**And here is my result including MLO, u-boot.img, etc:**

![Screenshot from 2020-08-27 23-23-58](https://user-images.githubusercontent.com/32474027/91456251-ff6cba00-e8bd-11ea-8128-b7e78e4cd0c7.png)







### See more a question:
1. [What is different between u-boot.bin and u-boot.img ?](https://stackoverflow.com/questions/29494321/what-is-different-between-u-boot-bin-and-u-boot-img)
2. [Can anyone explain the gcc cross-compiler naming convention?](https://stackoverflow.com/questions/5731495/can-anyone-explain-the-gcc-cross-compiler-naming-convention)


















