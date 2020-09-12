<h1> General-Purpose Input/Outputs </h1>

## Introduction to GPIO Interfacing
- Using the GPIOs on the expansion headers
- Using the buses (I2C, SPI, CAN Bus), or UARTs on the expansion headers
- Connecting USB modules (e.g., keyboards, Wi-Fi)
- Communicating through Ethernet/Wi-Fi/Bluetooth/ESP32 to electronics modules

## 1. GPIO Digital Output
- The AM335x has four banks (0–3) of 32 GPIOs that are numbered 0 to 31.\
This means that GPIO0_23 is GPIO 23 of 32 (0–31) on the first GPIO chip of four (0–3).\
As there are 32 GPIOs on each GPIO chip, the internal GPIO number corresponding to pin `GPIO0_23` is calculated as follows:
```text
(0×32) + 23 = 23
```
- The total range is GPIO 0 (GPIO0_0) to GPIO 127 (GPIO3_31), but as previously discussed, not all AM335x GPIOs are available on the headers of the different Beagle boards.

- Each pin has a default (reset) mode that is defined by the `boot configuration` of the device tree model.
- GPIO0_23 is available on P8 pin 13 on the BeagleBone

<p align="center"> <img width="350" src="https://user-images.githubusercontent.com/32474027/92597241-11992000-f2e2-11ea-9d13-0fcba923667c.png"/> </p>

**The input/output direction of a pin can be set using the GPIO sysfs entry `/sys/class/gpio/` or equivalently by using the `config-pin` tool**
```shell
debian@beaglebone:~$ config-pin -i p8.13
Pin name: P8_13
Function if no cape loaded: gpio
Function if cape loaded: default gpio gpio_pu gpio_pd gpio_input pwm
Function information: gpio0_23 default gpio0_23 gpio0_23 gpio0_23 gpio0_23 ehrpwm2b
Kernel GPIO id: 23
PRU GPIO id: 55
```
```shell
debian@beaglebone:/sys/class/gpio$ ls
export  gpiochip0  gpiochip32  gpiochip64  gpiochip96  unexport

root@beaglebone:/sys/class/gpio# echo 23 > export
root@beaglebone:/sys/class/gpio# ls
export	gpio23	gpiochip0  gpiochip32  gpiochip64  gpiochip96  unexport
```
## 2. GPIO Digital Input

- The circuit shown in Figure uses a normally open push button that is connected to the GPIO0_22, which is pin 19 on the BeagleBone P8 heade

<p align="center"> <img width="350" src="https://user-images.githubusercontent.com/32474027/92598618-0515c700-f2e4-11ea-994b-e158d61a9008.png"/> </p>

- In this example, you want to configure the button to have a **pull-down** resistor enabled on the input pin
```shell
root@beaglebone:/sys/class/gpio/gpio22# cat direction 
in
root@beaglebone:/sys/class/gpio/gpio22# cat value 
0
```
- When the button is pressed, and subsequently released, you’ll see this:
```shell
root@beaglebone:/sys/class/gpio/gpio22# cat value 
0
```
You will see that the input value is always 0 whether the button is pressed or released. That is because this input is connected via an internal *pull-down*
resistor to ground, meaning that the input is connected to ground in either case.

- Try configure the button to have a **pull-up** resistor enabled on the input pin (P9.12):
```shell
root@beaglebone:/sys/class/gpio# echo 60 > export
root@beaglebone:/sys/class/gpio/gpio60# cat direction 
in
root@beaglebone:/sys/class/gpio/gpio60# cat value 
1
```
When the push is pressed
```shell
root@beaglebone:/sys/class/gpio/gpio60# cat value 
0
```
-  You can check configure pin here:
```shell
root@beaglebone: cd /sys/kernel/debug/pinctrl/44e10800.pinmux/; cat pins
```
```text
...
pin 26 (44e10868.0) 00000027 pinctrl-single 
pin 27 (44e1086c.0) 00000007 pinctrl-single 
pin 28 (44e10870.0) 00000037 pinctrl-single 
pin 29 (44e10874.0) 00000037 pinctrl-single
...
```
- You can actually query the value at the memory address itself using C code that accesses `/dev/mem` directly.  Because `P9_12 ($PINS28)` is mapped at the memory
address `44e10870`
```shell
debian@beaglebone:~$ sudo ./devmen2 0x44e10870
/dev/mem opened.
Memory mapped at address 0xb6fe8000.
Value at address 0x44E10870 (0xb6fe8870): 0x37
```

## 3. GPIO Analog Output
- Waitting...
## 4. GPIO Analog Input
- Waitting...

------
<h1> Discuss About Source Code </h1>


- The button is attached to **P8_16 (GPIO 46)**, and the LED is attached to **P9_12 (GPIO 60)**. In these tests, the LED will light when the button is pressed.

<p align="center"> <img width="700" src="https://user-images.githubusercontent.com/32474027/92992054-da658180-f522-11ea-9b2f-e0abf1e7aed3.JPG" /> </p>

- **poll.cpp**: The downside of this code is that the program cannot perform other operations while awaiting the button press.
- **callback.cpp**: In this example, the main thread sleeps, but it could be performing other tasks. The significant change in this code is that when the `setEdgeType()` method is called, a new thread is created within the method, and it immediately returns control so that the main thread can continue to perform operations. The main thread simply sleeps for 10 seconds in this case before turning off the LED. If the button is pressed, the `activateLED()` function will be called. Whether the button is pressed or not, the LED will be turned off, and the program will exit after the sleep has finished.








