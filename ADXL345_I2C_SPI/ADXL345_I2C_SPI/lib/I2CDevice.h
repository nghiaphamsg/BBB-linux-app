/*
 * I2CDevice.h
 *
 *  Created on: May 3, 2020
 *  Author: NghiaPham
 */

#ifndef I2CDEVICE_H_
#define I2CDEVICE_H_

#include "BusDevice.h"

#define I2C_1		"/dev/i2c-1"
#define I2C_2		"/dev/i2c-2"

class I2CDevice:public BusDevice {
	public:
		I2CDevice(unsigned int bus, unsigned int device);
		virtual int open();
		virtual int write(unsigned char value);
		virtual int writeRegister(unsigned int registerAddress, unsigned char value);
		virtual unsigned char readRegister(unsigned int registerAddress);
		virtual unsigned char* readRegisters(unsigned int length, unsigned int fromAddress = 0);
		virtual void close();
		virtual void debugDumpRegisters(unsigned int length = 0xFF);
		virtual ~I2CDevice();
};


#endif /* I2CDEVICE_H_ */
