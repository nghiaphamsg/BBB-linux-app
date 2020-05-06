/*
 * tmp36Raw.cpp
 *
 *  Created on: May 6, 2020
 *  Author: NghiaPham
 */

#include <iostream>
#include <sstream>
#include <fstream>

#define ADC				0
#define ADC_PATH		"/sys/bus/iio/devices/iio:device0/in_voltage"

float getTemperature(int adcValue) {
	float currentVoltage = adcValue * (1.80f / 4096.0f);
	float diffDegreesC = (currentVoltage - 0.75f) / 0.01f;

	return (diffDegreesC + 25.0f);
}

int readAnalog(int place) {
	int rawValue;
	std::stringstream ss;
	ss << ADC_PATH << place << "_raw";

	std::fstream fs;
	fs.open(ss.str().c_str(), std::fstream::in);
	fs >> rawValue;
	fs.close();
	return rawValue;
}

int main() {

	float temp = getTemperature(readAnalog(ADC));
	std::cout << temp;
}
