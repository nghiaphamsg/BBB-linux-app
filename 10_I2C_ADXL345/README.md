<h1> Explore About I2C </h1>

## 1. General features of the I2C bus
- Only two signal lines are required for communication, the **Serial Data (SDA)** line for the bidirectional transmission of data, and the **Serial Clock (SCL)** line, which is used to synchronize the data transfer. Because the
bus uses this synchronizing clock signal, the data transfer is said to be synchronous. The transmission is said to be bidirectional because the same SDA wire can be used for sending and receiving data.

- Each device on the bus can act as a **master** or a **slave**. The master device is the one that initiates communication, and the slave device is the one that responds. Designated slave devices cannot initiate communication with
the master device

- Each slave device attached to the bus is pre-assigned a unique address, which is in either `7-bit` or `10-bit` form. In the following examples, 7-bit addressing is used, i.e., 0x00 to 0x7F (2^7
 = 128 = 0x80).
 
- It has true multi-master bus facilities, including collision detection and arbitration if two or more master devices activate at once.
 
- On-chip noise filtering is built in as standard.
 
 <p align="center"> <img width="700" src="https://user-images.githubusercontent.com/32474027/93086558-4508ef80-f6d2-11ea-9ff1-616498f6288c.png"/> </p>

- All output connections to the SDA and SCL lines are in open-drain configuration

- The I2C bus requires `pull-up resistors` (RP) on both the SDA and SCL lines. These are called termination resistors, and they usually have a value of between 1kΩ and 10kΩ. Their role is to pull the SDA and SCL lines up to VCC when no I2C device is pulling them down to GND

- The optional serial resistors (RS) usually have low values (e.g., 250Ω) and can help protect against overcurrent conditions.

## 2. I2C Devices on the Beagle Boards
-  I2C devices are visible in the `/dev/` directory
```shell
debian@beaglebone:~$ cd /dev/; ls -l i2c*
crw-rw---- 1 root i2c 89, 0 Sep 13 15:18 i2c-0
crw-rw---- 1 root i2c 89, 1 Sep 13 15:18 i2c-1
crw-rw---- 1 root i2c 89, 2 Sep 13 15:18 i2c-2
```

| H/W Bus | S/W Device | SDA Pin | SCL Pin | Description                        |
|---------|------------|---------|---------|------------------------------------|
| I2C0    | /dev/i2c-0 | n/a     | n/a     | internal bus for HDMI control      |
| I2C1    | /dev/i2c-1 | P9.18   | P9.17   | general i2c bus. disable by default|
| I2C2    | /dev/i2c-2 | P9.20   | P9.19   | general i2c bus. enable by default |


- You should ensure that it is supported by an LKM for your kernel (or by the kernel itself):
```shell
debian@beaglebone:/$ cd /lib/modules/4.14.108-ti-r113/kernel/drivers; ls
atm	    cdrom   firmware  hid    input  mfd   net	   remoteproc  spi	tty    w1
auxdisplay  char    fpga      hwmon  leds   misc  nfc	   rpmsg       staging	uio
block	    crypto  gpio      i2c    md     mmc   pinctrl  rtc	       target	usb
bluetooth   dax     gpu       iio    media  mtd   pps	   scsi        thermal	video
```
- And there is evidence of additional built-in drivers in:
```shell
debian@beaglebone:/$ cd /sys/bus/i2c/drivers; ls
```
- Wiring the Test Circuit

<p align="center"> <img width="400" src="https://user-images.githubusercontent.com/32474027/93089812-cebabc00-f6d6-11ea-946f-d5ac8b82f43f.png"/> </p>

### 3. Using Linux I2C-Tools
- Install these tools using the following command
```shell
debian@beaglebone:/$ sudo apt install i2c-tools
```
- Detect that the devices are present on the bus:
```shell
debian@beaglebone:/$ i2cdetect -l
i2c-1	i2c       	OMAP I2C adapter                	I2C adapter
i2c-2	i2c       	OMAP I2C adapter                	I2C adapter
i2c-0	i2c       	OMAP I2C adapter                	I2C adapter
```
- If the circuit is wired with an ADXL345 breakout board attached to the `/dev/i2c-1` bus. The ADXL345 breakout board occupies address 0x53, 
```shell
debian@beaglebone:/$ i2cdetect -y -r 1
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00:          -- -- -- -- -- -- -- -- -- -- -- -- -- 
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
50: -- -- -- 53 -- -- -- -- -- -- -- -- -- -- -- -- 
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
70: -- -- -- -- -- -- -- --
```
When `--` is displayed, the address was probed, but no device responded. If `UU` is displayed, then probing was skipped, as the address is already in use by a driver

- The **i2cset** command can be used to set a register (the ADXL345 out of power-saving mode, by writing `0x08` to the `POWER_CTL` register, which is at `0x2d`)
```shell
debian@beaglebone:/$ i2cset -y 1 0x53 0x2d 0x08
```
- The **i2cdump** command can be used to read in the values of the registers of the device attached to an I2C bus and display them in a hexadecimal block form
```shell
debian@beaglebone:/$ i2cdump -y 1 0x53 b
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f    0123456789abcdef
00: e5 00 00 00 00 00 00 00 00 00 00 00 00 00 00 4a    ?..............J
10: 82 00 30 00 00 00 04 3e 00 00 00 10 00 00 00 00    ?.0...?>...?....
20: 00 00 00 00 00 00 00 00 00 00 00 00 0a 08 00 00    ............??..
30: 83 00 02 00 11 00 fa 00 00 00 00 00 00 00 00 00    ?.?.?.?.........
40: e5 00 00 00 00 00 00 00 00 00 00 00 00 00 00 4a    ?..............J
50: 82 00 30 00 00 00 04 3e 00 00 00 10 00 00 00 00    ?.0...?>...?....
60: 00 00 00 00 00 00 00 00 00 00 00 00 0a 08 00 00    ............??..
70: 82 00 02 00 12 00 f9 00 00 00 00 00 00 00 00 00    ?.?.?.?.........
80: e5 00 00 00 00 00 00 00 00 00 00 00 00 00 00 4a    ?..............J
90: 80 00 30 00 00 00 04 3e 00 00 00 10 00 00 00 00    ?.0...?>...?....
a0: 00 00 00 00 00 00 00 00 00 00 00 00 0a 08 00 00    ............??..
b0: 82 00 01 00 12 00 f7 00 00 00 00 00 00 00 00 00    ?.?.?.?.........
c0: e5 00 00 00 00 00 00 00 00 00 00 00 00 00 00 4a    ?..............J
d0: 80 00 30 00 00 00 04 3e 00 00 00 10 00 00 00 00    ?.0...?>...?....
e0: 00 00 00 00 00 00 00 00 00 00 00 00 0a 08 00 00    ............??..
f0: 82 00 02 00 12 00 f9 00 00 00 00 00 00 00 00 00    ?.?.?.?.........
```
- The **i2cget** command can be used to read the value of a register (`0x32` is x-axis data 0)
```shell
debian@beaglebone:/$ i2cget -y 1 0x53 0x32
0x02
```
#### The master/slave access pattern in the first row is used as follows:
1. The master sends a start bit (i.e., it pulls SDA low, while SCL is high).
2. While the clock toggles, the 7-bit slave address is transmitted one bit at a time.
3. A read bit (1) or write bit (0) is sent, depending on whether the master wants to read or write to/from a slave register.
4. The slave responds with an acknowledge bit (ACK = 0).
5. In write mode, the master sends a byte of data one bit at a time, after which the slave sends back an ACK bit. To write to a register, the register address is sent, followed by the data value to be written.
6. Finally, to conclude communication, the master sends a stop bit (i.e., it allows SDA to float high, while SCL is high)

<p align="center"> <img width="1100" src="https://user-images.githubusercontent.com/32474027/93092788-db411380-f6da-11ea-9c5c-fad3110fad98.png"/> </p>


<p align="center"> <img width="600" src="https://user-images.githubusercontent.com/32474027/93098199-86ed6200-f6e1-11ea-8784-6a895c236351.JPG"/> </p>



