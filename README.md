<h1> Learn Embedded Linux Using Beaglebone Black </h1>

## Introduce
Learn ARM Linux systems, embedded linux building blocks, Beaglebone interfacing projects...
<p align="center"> <img width="500" src="https://elementztechblog.files.wordpress.com/2014/11/beaglebone_black.jpg" /> </p>


## Target
- Understanding various sub systems of AM335x (1GHz ARM® Cortex-A8) SOC such as GPIOs, I2C, SPI, MMC, etc...
- Understanding ROM–Uboot-Kernel boot process on Linux-ARM systems and testing.
- U-Boot, MLO, SPL, explanation and testing.
- Linux device tree
- Understanding platform devices and how it works.
- eMMC OS updating and booting new Debian OS.
- Interfacing external LEDs, temperature sensor, Acceleration/Gyroscope such as MPU 6050 or ADXL345 and code development.
- Using HTTP, the sensors can push numeric or alphanumeric data to the server, where it can be processed and visualized.
- Beaglebone networking
- Serial log (UART) used minicom tool

## Prepare

| Hardware              | Sortware      | Reference                                                                                |
|-----------------------|---------------|------------------------------------------------------------------------------------------|
| Beaglebone Black Rev.C| Ubuntu 18.04  | Exploring BeagleBone Tools and Techniques for Building with Embeddded Linux ®Derek Molloy|
| MPU6050               | VSC or Vim    | [AM335x ARM® Cortex™-A8 Microprocessors (MPUs) Technical Reference Manual](https://e2e.ti.com/cfs-file/__key/communityserver-discussions-components-files/790/AM335x_5F00_techincal_5F00_reference_5F00_manual.pdf)|
| ADXL345               | Cross compile | [AM335x Datasheet](https://www.ti.com/lit/ds/sprs717l/sprs717l.pdf?ts=1598362140689&ref_url=https%253A%252F%252Fwww.google.com%252F)|
| Button                | BusyBox       | [Beagleboard Cape Expansion Headers](https://elinux.org/Beagleboard:Cape_Expansion_Headers)|  
| Leds                  | Buildroot     | [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2](https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf)|
| 74HC595               | Minicom       | [MPU-6000/MPU-6050 Product Specification](https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf)|
| TMP36                 | GParted       | [ADXL345 Datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/ADXL345.pdf)|
| FT232RL USB Serial    |               | [TMP36 Datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/TMP35_36_37.pdf)|
| SD card (>4GB)        |               | [74HC595 Datasheet](https://www.onsemi.com/pub/Collateral/MC74HC595-D.PDF)|
| RTC-DS3231            |               | [RTC-DS3231](https://datasheets.maximintegrated.com/en/ds/DS3231.pdf) 
| GPS-Neo6M             |

## How to connecting BBB to PC using external USB TO UART converter
![Screenshot from 2020-08-25 22-18-12](https://user-images.githubusercontent.com/32474027/91179255-3c4f7a00-e721-11ea-8006-a49083c3fb5e.png)

## Instruction list 
01. [Booting process](https://github.com/nghiaphamsg/BeagleBone_Black_Embedded/tree/master/01_Booting_Process)
02. [How to use Busybox and Linux source for create RFS & uImage](https://github.com/nghiaphamsg/BeagleBone_Black_Embedded/tree/master/02_Gerenate_UBoot_RFS)
03. [How to use Buildroot for generate U-boot & RFS](https://github.com/nghiaphamsg/BeagleBone_Black_Embedded/tree/master/03_Buildroot)
04. [Exploring GPIO](https://github.com/nghiaphamsg/BeagleBone_Black_Embedded/tree/master/06_GPIO_Advanced)
05. [Exploring I2C](https://github.com/nghiaphamsg/BeagleBone_Black_Embedded/tree/master/10_I2C_ADXL345)
06. [Exploring SPI](https://github.com/nghiaphamsg/BeagleBone_Black_Embedded/tree/master/20_SPI_TEST)

11. [Other code example](https://github.com/nghiaphamsg/BeagleBone_Black_Embedded/tree/master/99_Extension)
12. [Exploring about Linux device driver](https://github.com/nghiaphamsg/BeagleBoneBlack_Linux_Device_Driver)
13. [CGI using C++ on the BeagleBone](http://derekmolloy.ie/beaglebone-cgicc/)
14. [Introduction to the BeagleBone Black Device Tree](https://learn.adafruit.com/introduction-to-the-beaglebone-black-device-tree/device-tree-overlays)\
   And other link [The Beaglebone Black and Device Tree Overlays](http://www.ofitselfso.com/BeagleNotes/Beaglebone_Black_And_Device_Tree_Overlays.php)
15. [Sharing internet using Network-Over-USB in BeagleBone Black](https://elementztechblog.wordpress.com/2014/12/22/sharing-internet-using-network-over-usb-in-beaglebone-black/)

