<h2> Step By Step How To Using Busybox Create RFS </h2>


#### Step 1: dowload busybox
```text
https://www.busybox.net/downloads/
```
#### Step 2: Apply default configuration
```shell
~busybox-1.32.0$ make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- defconfig
```
#### Step 3: Change default setting if you want
```shell
~busybox-1.32.0$ make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- menuconfig
```

#### Step 4: Generate the busybox binary and minimal file system
```shell
~busybox-1.32.0$ make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- CONFIG_PREFIX=<install_path> install
```
**After generated**
```text
    ├── bin
    ├── linuxrc -> bin/busybox
    ├── sbin
    └── usr
```

#### Step 5: Check size of file system and more information
```shell
~/RFS_Static/bin$ du -sh busybox
```
or 
```shell
~/RFS_Static/bin$ file busybox
```
--------------------------------------------------------------------------------------------
**ERROR**
```text
busybox-1.32.0/scripts/gcc-version.sh: line 11: arm-linux-gnueabihf-gcc: command not found
```
[See more here](https://stackoverflow.com/questions/36446721/arm-linux-gnueabi-g-command-not-found/42173507)



