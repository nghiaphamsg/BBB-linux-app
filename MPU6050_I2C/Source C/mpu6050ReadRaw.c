/*
 * 	mpu6050ReadRaw.c
 *	Created on: Apr 19, 2020
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

/* Full scale range accelerometer */
#define ACC_FS_RANGE_2				0x00
#define ACC_FS_RANGE_4				0x01
#define ACC_FS_RANGE_8				0x10
#define ACC_FS_RANGE_16				0x11

/* Full scale range gyroscope */
#define GYRO_FS_RANGE_250			0x00
#define GYRO_FS_RANGE_500			0x01
#define GYRO_FS_RANGE_1000			0x10
#define GYRO_FS_RANGE_2000			0x11

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

#define SLAVE_ADDRESS				0x68

#define I2C1_PATH					"/dev/i2c-1"
#define I2C2_PATH					"/dev/i2c-2"

int fd;

int mpu6050Write(uint8_t addr, uint8_t data) {
	char buff[2];
	buff[0] = addr;
	buff[1] = data;
	if(write(fd, buff, 2) != 2) {
		perror("Write failed. \n");
		return -1;
	}
	return 0;
}

int mpu6050Read(uint8_t base_addr, char *pBuffer, uint32_t length) {
	char buff[2];
	buff[0] = base_addr;
	if(write(fd, buff, 1) != 1) {
		perror("Write failed. \n");
		return -1;
	}

	if((read(fd, pBuffer, length)) != length) {
		perror("Read failed. \n");
		return -1;
	}
	return 0;
}

void mpu6050Init() {
	/* Wake-up*/
	mpu6050Write(MPU6050_PWR_MGMT_1, 0x00);
	usleep(500);

	/* Configure full scale */
	mpu6050Write(MPU6050_ACCEL_CONFIG, ACC_FS_RANGE_2);
	usleep(500);
	mpu6050Write(MPU6050_GYRO_CONFIG, GYRO_FS_RANGE_250);
	usleep(500);
}

void mpu6050ReadAcc(short int *pBuffer) {
	char accBuffer[6];
	mpu6050Read(MPU6050_ACCEL_XOUT_H, accBuffer, 6);

	pBuffer[0] = (int)( (accBuffer[0] << 8) | accBuffer[1] );
	pBuffer[1] = (int)( (accBuffer[2] << 8) | accBuffer[3] );
	pBuffer[2] = (int)( (accBuffer[4] << 8) | accBuffer[5] );
}

void mpu6050ReadGyro(short *pBuffer) {
	char gyroBuffer[6];
	mpu6050Read(MPU6050_GYRO_XOUT_H, gyroBuffer, 6);

	pBuffer[0] = ( (gyroBuffer[0] << 8) | gyroBuffer[1] );
	pBuffer[1] = ( (gyroBuffer[2] << 8) | gyroBuffer[3] );
	pBuffer[2] = ( (gyroBuffer[4] << 8) | gyroBuffer[5] );
}

int main() {
	double accX, accY, accZ, gyroX, gyroY, gyroZ;
	short accValue[3], gyroValue[3];

	if((fd = open(I2C1_PATH, O_RDWR)) < 0) {
        perror("Failed to open I2C device file.\n");
        return -1;
	}

	/* Set I2C slave address */
	if(ioctl(fd, I2C_SLAVE, SLAVE_ADDRESS) < 0) {
        perror("Failed to set I2C slave address.\n");
        close(fd);
        return -1;
	}

	mpu6050Init();

	while(1) {
		mpu6050ReadAcc(accValue);
		mpu6050ReadGyro(gyroValue);

		accX = (double) accValue[0]/ACC_FS_SENSITIVITY_0;
		accY = (double) accValue[1]/ACC_FS_SENSITIVITY_0;
		accZ = (double) accValue[2]/ACC_FS_SENSITIVITY_0;

		gyroX = (double) gyroValue[0]/GYRO_FS_SENSITIVITY_0;
		gyroY = (double) gyroValue[1]/GYRO_FS_SENSITIVITY_0;
		gyroZ = (double) gyroValue[2]/GYRO_FS_SENSITIVITY_0;

		printf("%0.2f	%0.2f	%0.2f\n", accX, accY, accZ);
		printf("%0.2f	%0.2f	%0.2f\n", gyroX, gyroY, gyroZ);
		usleep(50 * 1000);
	}
	return 0;
}
