/*
 * 	rtcds3231.c
 *	Created on: Sep 19, 2020
 *  Author: NghiaPham
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SLAVE_ADDRESS 0x68

#define I2C1_PATH "/dev/i2c-1"
#define I2C2_PATH "/dev/i2c-2"

#define BUFFER_SIZE 19

int fd;

int bcdToDec(char b)
{
    return (b / 16) * 10 + (b % 16);
}

void ds3231Write()
{
    char writeBuffer[1] = {0x00};
    if (write(fd, writeBuffer, 1) != 1)
    {
        perror("Failed to reset the read address\n");
        exit(1);
    }
}

char *ds3231Read()
{
    char *buff = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    if (read(fd, buff, BUFFER_SIZE) != BUFFER_SIZE)
    {
        perror("Failed to read in the buffer\n");
        exit(1);
    }
    return buff;
}

void ds3231Init(char *bus)
{
    fd = open(bus, O_RDWR);
    if (fd < 0)
    {
        perror("Failed to open I2C device file.\n");
        exit(1);
    }

    /* Set I2C slave address */
    if (ioctl(fd, I2C_SLAVE, SLAVE_ADDRESS) < 0)
    {
        perror("Failed to set I2C slave address.\n");
        close(fd);
        exit(1);
    }
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: %s [bus]\n", argv[0]);
        printf("	- bus: beaglebone black bus <1> or <2>\n");
        return -1;
    }

    if (strcmp(argv[1], "1") == 0)
        ds3231Init(I2C1_PATH);
    else if (strcmp(argv[1], "2") == 0)
        ds3231Init(I2C2_PATH);
    else
    {
        printf("Usage: %s [bus]\n", argv[0]);
        printf("  - bus: beaglebone black bus <1> or <2> \n");
        return -1;
    }

    ds3231Write();
    char *data = ds3231Read();

    printf("The RTC day is %01d\n", bcdToDec(data[3]));

    printf("The RTC date is %02d-%02d-%02d\n", bcdToDec(data[6]),
            bcdToDec(data[5]), bcdToDec(data[4]));

    printf("The RTC time is %02d:%02d:%02d\n", bcdToDec(data[2]),
           bcdToDec(data[1]), bcdToDec(data[0]));

    float temperature = data[0x11] + ((data[0x12] >> 6) * 0.25);
    printf("The temperature is %.2f°C\n", temperature);
    close(fd);

    return 0;
}
