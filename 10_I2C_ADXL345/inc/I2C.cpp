/*
 * 	I2C.cpp
 *  Created on: Apr 20, 2020
 */

#include <iostream>
#include <sstream>
#include <fcntl.h>
#include <stdio.h>
#include <iomanip>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include "I2C.h"

#define HEX(x) std::setw(2) << std::setfill('0') << std::hex << (int)(x)

I2C::I2C(unsigned int bus, unsigned int device)
{
	file = -1;
	this->device = device;
	this->bus = bus;
	init();
}

int I2C::init()
{
	std::string name;

	if (bus == 1)
		name = I2C_1;
	else
		name = I2C_2;

	if ((file = ::open(name.c_str(), O_RDWR)) < 0)
	{
		perror("I2C: failed to open the bus\n");
		return -1;
	}

	if (ioctl(file, I2C_SLAVE, device) < 0)
	{
		perror("I2C: Failed to configure to the device\n");
		return -1;
	}
	return 0;
}

int I2C::write(unsigned char value)
{
	unsigned char buff[1];
	buff[0] = value;

	if (::write(file, buff, 1) != 1)
	{
		perror("I2C: Failed to write to the device\n");
		return -1;
	}
	return 0;
}

int I2C::writeRegister(unsigned int registerAddress, unsigned char value)
{
	unsigned char buff[2];
	buff[0] = registerAddress;
	buff[1] = value;

	if (::write(file, buff, 2) != 2)
	{
		perror("I2C: Failed to write to the device\n");
		return -1;
	}
	return 0;
}

unsigned char I2C::readRegister(unsigned int registerAddress)
{
	write(registerAddress);
	unsigned char buff[1];

	if (::read(file, buff, 1) != 1)
	{
		perror("I2C: Failed to read in the value.\n");
		return -1;
	}
	return buff[0];
}

unsigned char *I2C::readRegisters(unsigned int length, unsigned int fromAddress)
{
	write(fromAddress);
	unsigned char *data = new unsigned char[length];

	if (::read(file, data, length) != (int)length)
	{
		perror("I2C: Failed to read in the value.\n");
		return NULL;
	}
	return data;
}

void I2C::debugDumpRegister(unsigned int length)
{
	std::cout << "Dumping Registers for Debug Purposes:" << std::endl;
	unsigned char *registers = readRegisters(length);

	for (int i = 0; i < (int)length; i++)
	{
		std::cout << HEX(*(registers + i)) << " ";
		if (i % 16 == 15)
			std::cout << std::endl;
	}
	std::cout << std::dec;
}

void I2C::close()
{
	::close(file);
	file = -1;
}

I2C::~I2C() {}