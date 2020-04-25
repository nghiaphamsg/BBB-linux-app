/*
 *  ADXL345_I2C.cpp
 *
 *  Created on: Apr 25, 2020
 *  Author: NghiaPham
 */


#include <iostream>
#include "ADXL345.h"

int main() {
	ADXL345 sensor(2, 0x53);					// I2C2, Address 0x53
	sensor.setResolution(ADXL345::NORMAL);
	sensor.setRange(ADXL345::PLUSMINUS_4_G);
    sensor.display();
	return 0;
}

