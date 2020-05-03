/*
 * BusDevice.h
 *
 *  Created on: May 3, 2020
 *  Author: NghiaPham
 */

#ifndef BUSDEVICE_H_
#define BUSDEVICE_H_

class BusDevice{
	protected:
		unsigned int bus;
		unsigned int device;
		int file;
	public:
		BusDevice(unsigned int bus, unsigned int device);
		virtual int open() = 0;
		virtual unsigned char readRegister(unsigned int registerAddress) = 0;
		virtual unsigned char* readRegisters(unsigned int length, unsigned int frommAddress = 0x00) = 0;
		virtual int write(unsigned char value) = 0;
		virtual int writeRegister(unsigned int registerAddress, unsigned char value) = 0;
		virtual void debugDumpRegisters(unsigned int number = 0xFF) = 0;
		virtual void close() = 0;
		virtual ~BusDevice();
};


#endif /* BUSDEVICE_H_ */
