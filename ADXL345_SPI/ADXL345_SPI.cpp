//============================================================================
// Name        : ADXL345_SPI.cpp
// Author      : NghiaPham
// Version     :
// Copyright   : Your copyright notice
// Description : SPI Protocol in C++, Ansi-style
//============================================================================

#include <iostream>
#include "SPIDevice.h"
#include "ADXL345.h"

int main() {
	   SPIDevice *busDevice = new SPIDevice(2,0);
	   busDevice->setSpeed(5000000);
	   std::cout << "The device ID is: " << (int) busDevice->readRegister(0x00) << std::endl;
	   busDevice->setMode(SPIDevice::MODE3);
	   busDevice->writeRegister(0x2D, 0x08);
	   busDevice->debugDumpRegisters(0x40);

	   std::cout << "Starting EBB ADXL345 SPI Test" << std::endl;
	   ADXL345 sensor(busDevice);
	   sensor.setResolution(ADXL345::NORMAL);
	   sensor.setRange(ADXL345::PLUSMINUS_4_G);
	   sensor.display();
	   std::cout << "End of EBB ADXL345 SPI Test" << std::endl;

}
