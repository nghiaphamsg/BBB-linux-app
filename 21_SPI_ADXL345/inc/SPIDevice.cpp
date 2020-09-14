/*
 *  SPIDevice.cpp
 *
 *  Created on: May 3, 2020
 *  Author: NghiaPham
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include <sstream>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#include "SPIDevice.h"

#define HEX(x) std::setw(2) << std::setfill('0') << std::hex << (int)(x)

SPIDevice::SPIDevice(unsigned int bus, unsigned int device)
	: BusDevice(bus, device) {
	std::stringstream s;
	s << SPI_PATH << bus << "." << device;
	this->fileName = std::string(s.str());
	this->bits = 8;
	this->speed = 500000;
	this->mode = MODE3;
	this->delay = 0;
	this->open();
}

int SPIDevice::open() {
	if((file = ::open(fileName.c_str(), O_RDWR)) < 0) {
		perror("SPI: Can't open device.");
		return -1;
	}
	if(setMode(mode) == -1) {
		return -1;
	}
	if(setBitsPerWord(bits) == -1) {
		return -1;
	}
	if(setSpeed(speed) == -1) {
		return -1;
	}
	return 0;
}

int SPIDevice::transfer(unsigned char send[], unsigned char receive[], int length) {
	struct spi_ioc_transfer	transfer;
	transfer.tx_buf = (unsigned long) send;
	transfer.rx_buf = (unsigned long) receive;
	transfer.len = length;
	transfer.speed_hz = this->speed;
	transfer.bits_per_word = this->bits;
	transfer.delay_usecs = this->delay;
	transfer.pad = 0;
	transfer.cs_change = 0;
	transfer.tx_nbits=0;
	transfer.rx_nbits=0;
	int status = ioctl(this->file, SPI_IOC_MESSAGE(1), &transfer);
	if (status < 0) {
		perror("SPI: SPI_IOC_MESSAGE Failed");
		return -1;
	}
	return status;
}

unsigned char SPIDevice::readRegister(unsigned int registerAddress) {
	unsigned char send[2], receive[2];
	memset(send, 0, sizeof send);
	memset(receive, 0, sizeof receive);

	send[0] = (unsigned char) (0x80 + registerAddress);
	this->transfer(send, receive, 2);
	return receive[1];
}

unsigned char* SPIDevice::readRegisters(unsigned int length, unsigned int fromAddress) {
	unsigned char* data = new unsigned char[length];
	unsigned char send[length+1], receive[length+1];
	memset(send, 0, sizeof send);

	send[0] =  (unsigned char) (0x80 + 0x40 + fromAddress);
	this->transfer(send, receive, length+1);
	memcpy(data, receive+1, length);

	return data;
}

int SPIDevice::write(unsigned char value) {
	unsigned char null_return = 0x00;
	this->transfer(&value, &null_return, 1);
	return 0;
}

int SPIDevice::write(unsigned char value[], int length) {
	unsigned char null_return = 0x00;
	transfer(value, &null_return, length);
	return 0;
}

int SPIDevice::writeRegister(unsigned int registerAddress, unsigned char value) {
	unsigned char send[2], receive[2];
	memset(receive, 0, sizeof receive);

	send[0] = (unsigned char) registerAddress;
	send[1] = value;

	this->transfer(send, receive, 2);
	return 0;
}

int SPIDevice::setMode(SPIDevice::SPIMODE mode) {
	this->mode = mode;

	if(ioctl(file, SPI_IOC_WR_MODE, &mode) == -1) {
		perror("SPI: Can't set SPI mode.");
		return -1;
	}
	if(ioctl(file, SPI_IOC_RD_MODE, &mode) == -1) {
		perror("SPI: Can't set SPI mode.");
		return -1;
	}
	return 0;
}

int SPIDevice::setBitsPerWord(uint8_t bits) {
	this->bits = bits;

	if(ioctl(file, SPI_IOC_WR_BITS_PER_WORD, &bits) == -1) {
		perror("SPI: Can't set SPI bits per word.");
		return -1;
	}
	if(ioctl(file, SPI_IOC_RD_BITS_PER_WORD, &bits) == -1) {
		perror("SPI: Can't set SPI bits per word.");
		return -1;
	}
	return 0;
}

int SPIDevice::setSpeed(uint32_t speed) {
	this->speed = speed;

	if(ioctl(file, SPI_IOC_WR_MAX_SPEED_HZ, &speed) == -1) {
		perror("SPI: Can't set max speed HZ.");
		return -1;
	}
	if(ioctl(file, SPI_IOC_RD_MAX_SPEED_HZ, &speed) == -1) {
		perror("SPI: Can't set max speed HZ.");
		return -1;
	}
	return 0;
}

void SPIDevice::close() {
	::close(file);
	file = -1;
}

void SPIDevice::debugDumpRegisters(unsigned int number) {
	std::cout << "SPI Mode: " << this->mode << std::endl;
	std::cout << "Bits per word: " << (int)this->bits << std::endl;
	std::cout << "Max speed: " << this->speed << std::endl;
	std::cout << "Dumping Registers for Debug Purposes:" << std::endl;
	unsigned char *registers = readRegisters(number);
	for(int i=0; i<(int)number; i++){
		std::cout << HEX(*(registers+i)) << " ";
		if (i%16==15) std::cout << std::endl;
	}
	std::cout << std::dec;
}

SPIDevice::~SPIDevice() {
	close();
}



