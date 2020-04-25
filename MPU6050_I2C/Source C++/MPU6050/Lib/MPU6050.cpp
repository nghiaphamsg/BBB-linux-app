/*
 * 	MPU6050.cpp
 *
 *  Created on: Apr 21, 2020
 *  Author: NghiaPham
 */

#include <iostream>
#include <fcntl.h>
#include <iomanip>
#include <unistd.h>

#include "MPU6050.h"

/* MPU6050 power and configure register addresses */
#define MPU6050_PWR_MGMT_1			0x6B
#define MPU6050_GYRO_CONFIG			0x1B
#define MPU6050_ACCEL_CONFIG		0x1C

/* Addresses of MPU6050 from which you will fetch accelerometer x,y,z high and low values */
#define MPU6050_ACCEL_XOUT_H		0x3B
#define MPU6050_ACCEL_XOUT_L		0x3C
#define MPU6050_ACCEL_YOUT_H		0x3D
#define MPU6050_ACCEL_YOUT_L		0x3E
#define MPU6050_ACCEL_ZOUT_H		0x3F
#define MPU6050_ACCEL_ZOUT_L		0x40

/* Addresses of MPU6050 from which you will fetch gyroscope x,y,z high and low values */
#define MPU6050_GYRO_XOUT_H			0x43
#define MPU6050_GYRO_XOUT_L			0x44
#define MPU6050_GYRO_YOUT_H			0x45
#define MPU6050_GYRO_YOUT_L			0x46
#define MPU6050_GYRO_ZOUT_H			0x47
#define MPU6050_GYRO_ZOUT_L			0x48

/* Accelerometer Sensitivity Scale Factor */
#define ACC_FS_SENSITIVITY_0		16384
#define ACC_FS_SENSITIVITY_1		8192
#define ACC_FS_SENSITIVITY_2		4096
#define ACC_FS_SENSITIVITY_3		2048

/* Gyroscope Sensitivity Scale Factor */
#define GYRO_FS_SENSITIVITY_0		131
#define GYRO_FS_SENSITIVITY_1		65.5
#define GYRO_FS_SENSITIVITY_2		32.8
#define GYRO_FS_SENSITIVITY_3		16.4

short MPU6050::combineRegisters(unsigned char msb, unsigned char lsb){
   return ((short)msb << 8) | (short)lsb;
}

void MPU6050::updateRegisters(){
   char accDataFormat = 0x00;
   char gyroDataFormat = 0x00;
   accDataFormat |= ((this->accRange) << 3);
   this->writeRegister(MPU6050_ACCEL_CONFIG, accDataFormat);
   gyroDataFormat |= ((this->gyroRange) << 3);
   this->writeRegister(MPU6050_GYRO_CONFIG, gyroDataFormat);
}

void MPU6050::calculateGravity() {
	int accFsSensi = 0, gyroFsSensi = 0;

	/* Calculate for accelerometer	*/
	switch(MPU6050::accRange){
		case ACC_FS_SEL_2G:
			gyroFsSensi = ACC_FS_SENSITIVITY_0;
			break;
		case ACC_FS_SEL_4G:
			gyroFsSensi = ACC_FS_SENSITIVITY_1;
			break;
		case ACC_FS_SEL_8G:
			gyroFsSensi = ACC_FS_SENSITIVITY_2;
			break;
		default:
			gyroFsSensi = ACC_FS_SENSITIVITY_3;
			break;
	}

	this->accX_G = (float)accX/gyroFsSensi;
	this->accY_G = (float)accY/gyroFsSensi;
	this->accZ_G = (float)accZ/gyroFsSensi;

	/* Calculate for gyroscope	*/
	switch(MPU6050::accRange){
		case GYRO_FS_SEL_250:
			accFsSensi = GYRO_FS_SENSITIVITY_0;
			break;
		case GYRO_FS_SEL_500:
			accFsSensi = GYRO_FS_SENSITIVITY_1;
			break;
		case GYRO_FS_SEL_1000:
			accFsSensi = GYRO_FS_SENSITIVITY_2;
			break;
		default:
			accFsSensi = GYRO_FS_SENSITIVITY_3;
			break;
	}

	this->gyroX_G = (double)gyroX/accFsSensi;
	this->gyroY_G = (double)gyroY/accFsSensi;
	this->gyroZ_G = (double)gyroZ/accFsSensi;
}

MPU6050::MPU6050(unsigned int I2CBus, unsigned int I2CAddress)
	:I2C(I2CBus, I2CAddress) {
	this->I2CBus = I2CBus;
	this->I2CAddress = I2CAddress;
	this-> accX = 0;
	this-> accY = 0;
	this-> accZ = 0;
	this-> gyroX = 0;
	this-> gyroY = 0;
	this-> gyroZ = 0;
	this->accX_G = 0.0f;
	this->accY_G = 0.0f;
	this->accZ_G = 0.0f;
	this->gyroX_G = 0.0f;
	this->gyroY_G = 0.0f;
	this->gyroZ_G = 0.0f;
	this->registers = NULL;
	this->accRange = MPU6050::ACC_FS_SEL_16G;
	this->gyroRange = MPU6050::GYRO_FS_SEL_2000;
	this->writeRegister(MPU6050_PWR_MGMT_1, 0x00);
	updateRegisters();
}

int MPU6050::readSensor() {
	this->registers = this->readRegisters(BUFF_SIZE, 0x00);

	accX = this->combineRegisters(*(registers + MPU6050_ACCEL_XOUT_H), *(registers + MPU6050_ACCEL_XOUT_L));
	accY = this->combineRegisters(*(registers + MPU6050_ACCEL_YOUT_H), *(registers + MPU6050_ACCEL_YOUT_L));
	accZ = this->combineRegisters(*(registers + MPU6050_ACCEL_ZOUT_H), *(registers + MPU6050_ACCEL_ZOUT_L));
	this->accRange = (MPU6050::ACC_RANGE) ((*(registers + MPU6050_ACCEL_CONFIG) & 0x18) >> 3);

	gyroX = this->combineRegisters(*(registers + MPU6050_GYRO_XOUT_H), *(registers + MPU6050_GYRO_XOUT_L));
	gyroY = this->combineRegisters(*(registers + MPU6050_GYRO_YOUT_H), *(registers + MPU6050_GYRO_YOUT_L));
	gyroZ = this->combineRegisters(*(registers + MPU6050_GYRO_ZOUT_H), *(registers + MPU6050_GYRO_ZOUT_L));
	this->gyroRange = (MPU6050::GYRO_RANGE) ((*(registers + MPU6050_GYRO_CONFIG) & 0x18) >> 3);

	calculateGravity();
	return 0;
}

void MPU6050::setAccRange(MPU6050::ACC_RANGE accRange) {
	this->accRange = accRange;
	updateRegisters();
}

void MPU6050::setGyroRange(MPU6050::GYRO_RANGE gyroRange) {
	this->gyroRange = gyroRange;
	updateRegisters();
}

void MPU6050::display(){
	while(1){
		readSensor();
		std::cout << std::setprecision(2)
		<< "ACC-X: "<< this->getAccXGravity()
		<< "    ACC-Y:" << this->getAccYGravity()
		<< "    ACC-Z:" << this->getAccZGravity()
		<< std::setprecision(4)
		<< "    GYRO-X: "<< this->getGyroXGravity()
		<< "    GYRO-Y:" << this->getGyroYGravity()
		<< "    GYRO-Z:" << this->getGyroZGravity()
		<< "     \r"<< std::flush;
		usleep(100000);
	}
}

MPU6050::~MPU6050() {}

