/*
 *  ADXL345_I2C.cpp
 *  Created on: Apr 25, 2020
 */

#include <iostream>
#include "inc/ADXL345.h"

int main()
{
	/* I2C2, Address 0x53 */
	ADXL345 sensor(1, 0x53);

	sensor.setResolution(ADXL345::NORMAL);
	sensor.setRange(ADXL345::PLUSMINUS_4_G);
	sensor.display();

	return 0;
}