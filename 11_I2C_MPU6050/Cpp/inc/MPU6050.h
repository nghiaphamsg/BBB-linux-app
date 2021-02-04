/*
 * 	MPU6050.h
 *  Created on: Apr 21, 2020
 */

#ifndef LIB_MPU6050_H_
#define LIB_MPU6050_H_

#include "I2C.h"

#define BUFF_SIZE		117

class MPU6050 : protected I2C
{
public:
	/* Full scale range accelerometer */
	enum ACC_RANGE
	{
		ACC_FS_SEL_2G = 0,
		ACC_FS_SEL_4G = 1,
		ACC_FS_SEL_8G = 2,
		ACC_FS_SEL_16G = 3
	};

	/* Full scale range gyroscope */
	enum GYRO_RANGE
	{
		GYRO_FS_SEL_250 = 0,
		GYRO_FS_SEL_500 = 1,
		GYRO_FS_SEL_1000 = 2,
		GYRO_FS_SEL_2000 = 3
	};

private:
	unsigned int I2CBus, I2CAddress;
	unsigned char *registers;
	MPU6050::ACC_RANGE accRange;
	MPU6050::GYRO_RANGE gyroRange;
	short accX, accY, accZ, gyroX, gyroY, gyroZ;
	float accX_G, accY_G, accZ_G;
	double gyroX_G, gyroY_G, gyroZ_G;
	short combineRegisters(unsigned char msb, unsigned char lsb);
	virtual void updateRegisters();
	virtual void convertAccRawToGravity();
	virtual void convertGyroRawToGravity();

public:
	MPU6050(unsigned int I2CBus, unsigned int I2CAddress = 0x68);
	virtual int readSensor();
	virtual void setAccRange(MPU6050::ACC_RANGE accRange);
	virtual void setGyroRange(MPU6050::GYRO_RANGE gyroRange);
	virtual MPU6050::ACC_RANGE getAccRange() { return this->accRange; }
	virtual MPU6050::GYRO_RANGE getGyroRange() { return this->gyroRange; }
	virtual float getAccXGravity() { return accX_G; }
	virtual float getAccYGravity() { return accY_G; }
	virtual float getAccZGravity() { return accZ_G; }
	virtual float getGyroXGravity() { return gyroX_G; }
	virtual float getGyroYGravity() { return gyroY_G; }
	virtual float getGyroZGravity() { return gyroZ_G; }

	/* Debugging method to display */
	virtual void display();
	virtual ~MPU6050();
};

#endif /* LIB_MPU6050_H_ */