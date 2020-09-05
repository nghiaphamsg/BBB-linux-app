/*
 *  MPU6050_I2C.cpp
 *
 *  Created on: Apr 22, 2020
 *  Author: NghiaPham
 */

#include <iostream>
#include "MPU6050.h"

int main() {

	MPU6050 sensor(1, 0x68);
	sensor.setAccRange(MPU6050::ACC_FS_SEL_2G);
	sensor.setGyroRange(MPU6050::GYRO_FS_SEL_250);
    sensor.display();
	return 0;
}
