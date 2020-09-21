<h1> UART Applications: GPS (Using library) </h1>

## 1. Board UART connection to the GPS module

| Beaglebone Black  | GPS (Neo-6M)  |
|-------------------|---------------|
| VSS (3.3v)        | VCC           |
| GND               | GND           |
| UART4 RX (P9.11)  | RX            |
| UART4 TX (P9.13)  | TX            |

<p align="center"><img width="800" src="https://user-images.githubusercontent.com/32474027/93780786-89146b00-fc63-11ea-9874-cb041681454d.JPG" /></p>

## 2. Execute with third library

- **Walter Dal Mut** (@walterdalmut) has made a C library available for interfacing to GPS sensors. The library can be easily integrated within your project to utilize GPS, as follows

```shell
debian@beaglebone:/$ git clone git://github.com/wdalmut/libgps
debian@beaglebone:/$ cd libgps; make

debian@beaglebone:/libgps$ sudo make install
```
- **Note:** Modify UART 04 bus in `include.h` file

- Run GPS after compiled
```shell
debian@beaglebone:~/41_UART_GPS$ make
debian@beaglebone:~/41_UART_GPS$ ./gps
```

## 3. Using gpsmon
- The GPS module outputs **NEMA 0183 sentences**, which can be decoded to provide information about the sensor’s position, direction, velocity, and so on. There is a lot of work involved in decoding the sentences, so it is best to use a client application to test the performance of your sensor.

```shell
debian@beaglebone:/$ sudo apt install gpsd-clients
debian@beaglebone:/$ gpsmon /dev/ttyO4/
```
