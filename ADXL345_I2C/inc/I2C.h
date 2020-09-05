/*
 * 	I2C.h
 *
 *  Created on: Apr 20, 2020
 *  Author: NghiaPham
 */

#ifndef LIB_I2C_H_
#define LIB_I2C_H_


#define I2C_1		"/dev/i2c-1"
#define I2C_2		"/dev/i2c-2"

class I2C {
	private:
		unsigned int bus;
		unsigned int device;
		int file;
	public:
		I2C(unsigned int bus, unsigned int device);
		virtual int init();
		virtual int write(unsigned char value);
		virtual int writeRegister(unsigned int registerAddress, unsigned char value);
		virtual unsigned char readRegister(unsigned int registerAddress);
		virtual unsigned char* readRegisters(unsigned int length, unsigned int fromAddress = 0);
		virtual void close();
		virtual void debugDumpRegister(unsigned int length = 0xFF);
		virtual ~I2C();
};

#endif /* LIB_I2C_H_ */
