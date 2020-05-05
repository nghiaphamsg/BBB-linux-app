/*
 ============================================================================
 Name        : 74HC595_SPI.c
 Author      : NghiaPham
 Version     :
 Copyright   : Your copyright notice
 Description : Control LED by 74HC595
 ============================================================================
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <linux/spi/spidev.h>

#define SPI_PATH "/dev/spidev1.0"

const unsigned char symbols[16] = {                   //(msb) HGFEDCBA (lsb)
     0b00111111, 0b00000110, 0b01011011, 0b01001111,  // 0123
     0b01100110, 0b01101101, 0b01111101, 0b00000111,  // 4567
     0b01111111, 0b01100111, 0b01110111, 0b01111100,  // 89Ab
     0b00111001, 0b01011110, 0b01111001, 0b01110001   // CdEF
};

int transfer(int fd, unsigned char send[], unsigned char receive[], int length){
	struct spi_ioc_transfer transfer;
	transfer.tx_buf = (unsigned long) send;
	transfer.rx_buf = (unsigned long) receive;
	transfer.len = length;
	transfer.speed_hz = 1000000;
	transfer.bits_per_word = 8;
	transfer.delay_usecs = 0;
	transfer.pad = 0;
	transfer.cs_change = 0;
	transfer.tx_nbits = 0;
	transfer.rx_nbits = 0;
	transfer.word_delay_usecs = 0;

	int status = ioctl(fd, SPI_IOC_MESSAGE(1), &transfer);
	if (status < 0) {
		perror("SPI: SPI_IOC_MESSAGE Failed");
		return -1;
	}
	return status;
}
int main(){
	unsigned int fd, i=0; // file handle and loop counter
	unsigned char null = 0x00; // sending only a single char
	uint8_t bits = 8, mode = 3; // 8-bits per word, SPI mode 3
	uint32_t speed = 1000000; // Speed is 1 MHz
	// The following calls set up the SPI bus properties
	if ((fd = open(SPI_PATH, O_RDWR))<0){
		perror("SPI Error: Can't open device.");
		return -1;
	}
	if (ioctl(fd, SPI_IOC_WR_MODE, &mode)==-1){
		perror("SPI: Can't set SPI mode.");
		return -1;
	}
	if (ioctl(fd, SPI_IOC_RD_MODE, &mode)==-1){
		perror("SPI: Can't get SPI mode.");
		return -1;
	}
	if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits)==-1){
		perror("SPI: Can't set bits per word.");
		return -1;
	}
	if (ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits)==-1){
		perror("SPI: Can't get bits per word.");
		return -1;
	}
	if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed)==-1){
		perror("SPI: Can't set max speed HZ");
		return -1;
	}
	if (ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed)==-1){
		perror("SPI: Can't get max speed HZ.");
		return -1;
	}
	// Check that the properties have been set
	printf("SPI Mode is: %d\n", mode);
	printf("SPI Bits is: %d\n", bits);
	printf("SPI Speed is: %d\n", speed);
	printf("Counting through all of the LEDs:\n");

	for (i = 0; i <= 255; i++)
	{
	// This function can send and receive data, but just sending here
		if (transfer(fd, (unsigned char*) &i, &null, 1) == -1){
			perror("Failed to update the display");
			return -1;
		}
		printf("%4d\r", i);
		fflush(stdout);
		usleep(100000);
	}
	close(fd);
	return 0;
}
