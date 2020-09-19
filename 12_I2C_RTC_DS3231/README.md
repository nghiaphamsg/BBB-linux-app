<h1> Discuss About Real-Time Clock (RTC-DS3231) </h1>


### 1. How to check RTC device driver build-in kernel
```shell
debian@beaglebone:/lib/modules/4.14.108-ti-r113/kernel/drivers/rtc$ ls
rtc-bq4802.ko.xz  rtc-ds1553.ko.xz  rtc-hid-sensor-time.ko.xz  rtc-msm6242.ko.xz
rtc-cmos.ko.xz	  rtc-ds1685.ko.xz  rtc-m48t35.ko.xz	       rtc-rp5c01.ko.xz
rtc-ds1286.ko.xz  rtc-ds1742.ko.xz  rtc-m48t59.ko.xz	       rtc-stk17ta8.ko.xz
rtc-ds1511.ko.xz  rtc-ds2404.ko.xz  rtc-m48t86.ko.xz	       rtc-v3020.ko.xz
```
or
```shell
debian@beaglebone:/sys/bus/i2c/drivers$ ls
adihdmi     palmas	    rtc-ds1672	  rtc-max6900	   rtc-rx8010	stmpe-i2c	     tps65217
adv7511     pca953x	    rtc-ds3232	  rtc-pcf2127-i2c  rtc-rx8025	tda998x		     tps65218
ar1021_i2c  pca9685-pwm     rtc-em3027	  rtc-pcf85063	   rtc-rx8581	tfp410
at24	    pcf8583	    rtc-fm3130	  rtc-pcf8523	   rtc-s35390a	tlv320aic23-codec
bq32k	    rtc-ab-b5ze-s3  rtc-hym8563   rtc-pcf8563	   rtc-x1205	tlv320aic31xx-codec
dummy	    rtc-abx80x	    rtc-isl12022  rtc-rs5c372	   sii902x	tlv320aic3x-codec
edt_ft5x06  rtc-ds1307	    rtc-isl1208   rtc-rv3029c2	   silead_ts	tmp102
ir-kbd-i2c  rtc-ds1374	    rtc-m41t80	  rtc-rv8803	   ssd1307fb	tpm_i2c_atmel
```
- The `DS3231` is compatible with the `DS1307 LKM` (**rtc-ds1307.ko**) or built-in kernel code

### 2. Wiring the Test Circuit

| BeagleBone Black | RTC-DS3231 | 
|------------------|------------|
| VCC (3.3)        | VCC        |
| GND              | GND        |
| SDA(P9.18)       | SDA        |
| SCL(P9.17)       | SCL        |

<p align="center"> <img width="450" src="https://user-images.githubusercontent.com/32474027/93669071-38b6d500-facc-11ea-80a5-e1d2b8ec8af5.JPG" /></p>

### 3. How to use RTC device driver
- Linux supports the use of RTCs directly within the OS using LKMs. The `DS3231` is compatible with the `rtc-ds1307.ko` LKM or built-in kernel code and can be associated with the bus device at address **0x68** using the following
- Enable bus for create a new rtc device
```shell
debian@beaglebone: cd /sys/class/i2c-adapter/i2c-1/
debian@beaglebone:/sys/class/i2c-adapter/i2c-1$ sudo echo "ds1307 0x68" > new_device
```
```shell
debian@beaglebone:/sys/class/i2c-adapter/i2c-1$ dmesg | grep ds1307
[ 2614.916158] rtc-ds1307 1-0068: registered as rtc1
[ 2614.916272] i2c i2c-1: new_device: Instantiated device ds1307 at 0x68
```
- Get date/time
```shell
debian@beaglebone:/$ sudo hwclock -r -f /dev/rtc1 
2020-09-19 23:18:18.076304+0000
```
- Set date/time
```shell
debian@beaglebone:/$ sudo hwclock --set --date="0000-00-00 00:00:00" -f /dev/rtc1 
```
- If you want delete module
```shell
debian@beaglebone:/sys/class/i2c-adapter/i2c-1$ sudo echo "0x68" > delete_device
```

### 4. How to use systemd service
- Create a new service file with `service` extension
```shell
debian@beaglebone:/$ cd /lib/systemd/system; vi ebb_clock.service
```
- Custom service must be enabled
```shell
debian@beaglebone:/$ sudo systemctl enable ebb_clock
```
- You can check the service status
```shell
 debian@beaglebone:/$ sudo systemctl status ebb_clock
```
- How to disable service
```shell
 debian@beaglebone:/$ sudo systemctl disable ebb_clock
```

