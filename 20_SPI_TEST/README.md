<h1> SPI Bus </h1>

### 1. SPI
- The `SPI master` defines the clock frequency at which to synchronize the data communication channels.
- The SPI master pulls the `chip select (CS)` line low, which activates the client device—it is therefore said to be active low. This line is also known as `slave select (SS)`.
- After a short delay, the SPI master issues clock cycles, sending data out on the **master out - slave in (MOSI) line** and receiving data on the **master in slave out (MISO) line**. The SPI slave device reads data from the MOSI line and transmits data on the MISO line. One bit is sent and one bit is received on each clock cycle. The data is usually sent in 1-byte (8-bit) chunks.
- When complete, the SPI master stops sending a clock signal and then pulls the CS line **high**, deactivating the SPI slave device.

**SPI communication mode**
| Mode  | Clock Polarity (CPOL) | Clock Phase (CPHA)                                            | 
|-------|-----------------------|---------------------------------------------------------------|
| 0     | 0 (low at idle)       | 0 (data captured on the rising edge of the clock signal)      |
| 1     | 0 (low at idle)       | 1 (data captured on the falling edge of the clock signal)     |
| 2     | 1 (high at idle)      | 0 (data captured on the falling edge of the clock signal)     |
| 3     | 1 (high at idle)      | 1 (data captured on the rising edge of the clock signal)      |


### 2. SPI on Beaglebone Black
- SPI Pins on the Beagle Boards

| Pins          | SPI0 (1.0/1.1)  | SPI1 (2.0/2.1)  |
|---------------|-----------------|-----------------|
| Chip Select   | P9.17           | P9.28           |
| MOSI          | P9.18           | P9.29           |     
| MISO          | P9.21           | P9.30           |
| Clock         | P9.22           | P9.31           |

- SPI0: spidev1.0 spidev1.1
- SPI1: spidev2.0 spidev2.1

If this code is executed without connecting to the SPI0 pins, then the output displayed by the `spitest` program will consist of a block of **0x00** or **0xFF** values, depending on whether the MISO pin is configured in pull-down or pull-up configuration.

```shell
debian@beaglebone:~$ make
debian@beaglebone:~$ ./spitest -D /dev/spidev1.0
spi mode: 0
bits per word: 8
max speed: 500000 Hz (500 KHz)

00 00 00 00 00 00 
00 00 00 00 00 00 
00 00 00 00 00 00 
00 00 00 00 00 00 
00 00 00 00 00 00 
00 00 00 00 00 00 
00 00
```

If the SPI MOSI and SPI MISO pins are connected together.
```shell
debian@beaglebone:~$ ./spitest -D /dev/spidev1.1
spi mode: 0
bits per word: 8
max speed: 500000 Hz (500 KHz)

FF FF FF FF FF FF 
40 00 00 00 00 95 
FF FF FF FF FF FF 
FF FF FF FF FF FF 
FF FF FF FF FF FF 
DE AD BE EF BA AD 
F0 0D
```

### 3. Compare of I2C vs SPI on BBB

|               | I2C                                                                   | SPI |
|---------------|-----------------------------------------------------------------------|-------------------------------------------------------------------|
| Connectivity  | Two wires, to which up to 128 addressable devices can be attached.    | Typically four wires and requires additional logic for more than one slave device.| 
| Data rate     | I2C fast mode is 400 kHz. It uses half-duplex communication.          | Faster performance (~10MHz) on the Beagle boards. It uses full duplex (except the three-wire variant).|
| Hardware      | Pull-up resistors required.                                           | No Pull-up resistors required. |
| Support       | Fully supported with two external buses (plus one HDMI).              | Fully supported with one bus. There are two slave selection pins on all boards.|
| Features      | Can have multiple masters. Slaves have addresses, acknowledge transfer, and can control the flow of data. | Simple and fast, but only one master device, no addressing, and no slave control of data flow.|
| Application   | Intermittently accessed devices, e.g., RTCs, EEPROMs                  | For devices that provide data streams, e.g., ADCs.|


