/*
 * ADXL345_I2C_SPI.cpp
 *
 *  Created on: May 3, 2020
 *  Author: NghiaPham
 */
#include <iostream>
#include "SPIDevice.h"
#include "I2CDevice.h"
#include "ADXL345.h"

int main() {
	std::cout << "Starting ADXL345 SPI Test" << std::endl;

	SPIDevice spi(2,0);
	spi.setMode(SPIDevice::MODE3);
	spi.setSpeed(1000000);

	ADXL345 spiSensor(&spi);
	spiSensor.setResolution(ADXL345::NORMAL);
	spiSensor.setRange(ADXL345::PLUSMINUS_8_G);
	spiSensor.display();

	std::cout << "Starting ADXL345 I2C Test" << std::endl;
	I2CDevice i2c(1, 0x53);
	ADXL345 i2cSensor(&i2c);

	i2cSensor.setResolution(ADXL345::NORMAL);
	i2cSensor.setRange(ADXL345::PLUSMINUS_4_G);
	i2cSensor.display();
}
