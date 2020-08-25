<h1> Embedded Linux using Beaglebone Black </h1>

## Introduce
Learn ARM Linux systems, embedded linux building blocks, Busybox, Beaglebone interfacing projects and much more.

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

| Hardware             |Sortware      |Reference                                                                                |
|----------------------|--------------|-----------------------------------------------------------------------------------------|
|Beaglebone Black Rev.C|Ubuntu 18.04  |Exploring BeagleBone Tools and Techniques for Building with Embeddded Linux ®Derek Molloy|
|MPU6050               |Eclipse IDE   |[AM335x ARM® Cortex™-A8 Microprocessors (MPUs) Technical Reference Manual](https://e2e.ti.com/cfs-file/__key/communityserver-discussions-components-files/790/AM335x_5F00_techincal_5F00_reference_5F00_manual.pdf)|
|ADXL345               |Vim           |[AM335x Datasheet](https://www.ti.com/lit/ds/sprs717l/sprs717l.pdf?ts=1598362140689&ref_url=https%253A%252F%252Fwww.google.com%252F)|
|Button                |GCC8/G++8     |[MPU-6000/MPU-6050 Product Specification](https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf)|  
|Leds                  |BusyBox       |[MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2](https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf)|
|74HC595               |CronTab       |[ADXL345 Datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/ADXL345.pdf)|
|TMP36                 |ThingSpeak    |[74HC595 Datasheet](https://www.onsemi.com/pub/Collateral/MC74HC595-D.PDF)|
|FT232RL USB Serial    |Socket I/O    |[TMP36 Datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/TMP35_36_37.pdf)|
|SD card (>4GB)        |Minicom
|LCD (Not Used)        |GParted

## How to connecting BBB to PC using external USB TO UART converter
![Screenshot from 2020-08-25 22-18-12](https://user-images.githubusercontent.com/32474027/91179255-3c4f7a00-e721-11ea-8006-a49083c3fb5e.png)

## 
