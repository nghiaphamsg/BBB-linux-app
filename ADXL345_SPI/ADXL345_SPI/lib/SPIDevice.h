/*
 * SPIDevice.h
 *
 *  Created on: May 3, 2020
 *  Author: NghiaPham
 */

#ifndef SPIDEVICE_H_
#define SPIDEVICE_H_


#include "BusDevice.h"
#include <string>

#define SPI_PATH			"/dev/spidev"

class SPIDevice:public BusDevice {
	public:
		enum SPIMODE {
			MODE0 = 0,
			MODE1 = 1,
			MODE2 = 2,
			MODE3 = 3
		};
	private:
		std::string fileName;
		SPIMODE mode;
		uint8_t bits;
		uint16_t delay;
		uint32_t speed;
	public:
		SPIDevice(unsigned int bus, unsigned int device);
		virtual int open();
		virtual int transfer(unsigned char read[], unsigned char write[], int length);
		virtual unsigned char readRegister(unsigned int registerAddress);
		virtual unsigned char* readRegisters(unsigned int length, unsigned int fromAddress = 0x00);
		virtual int write(unsigned char value);
		virtual int write(unsigned char value[], int length);
		virtual int writeRegister(unsigned int registerAddress, unsigned char value);
		virtual int setMode(SPIDevice::SPIMODE mode);
		virtual int setBitsPerWord(uint8_t bits);
		virtual int setSpeed(uint32_t speed);
		virtual void close();
		virtual ~SPIDevice();
		virtual void debugDumpRegisters(unsigned int number = 0xFF);
};


#endif /* SPIDEVICE_H_ */
