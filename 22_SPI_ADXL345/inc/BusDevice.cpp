/*
 * 	BusDevice.cpp
 *  Created on: May 3, 2020
 */

#include "BusDevice.h"

BusDevice::BusDevice(unsigned int bus, unsigned int device)
{
	this->bus = bus;
	this->device = device;
	this->file = -1;
}

BusDevice::~BusDevice() {}