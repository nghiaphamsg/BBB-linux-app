/*
 *  BusDevice.cpp
 *
 *  Created on: Apr 28, 2020
 *  Author: NghiaPham
 */

#include "BusDevice.h"

BusDevice::BusDevice(unsigned int bus, unsigned int device) {
	this->bus = bus;
	this->device = device;
	this->file = -1;
}

BusDevice::~BusDevice() { }
