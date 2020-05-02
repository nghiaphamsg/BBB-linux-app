/*
 * ADXL345_SPI.cpp
 *
 *  Created on: May 3, 2020
 *      Author: nekobot
 */

#ifndef ADXL345_CPP_
#define ADXL345_CPP_

#include "ADXL345.h"
#include <iostream>
#include <unistd.h>
#include <math.h>
#include <iomanip>


//From Table 19. of the ADXL345 Data sheet
#define DEVID          0x00   //Device ID
#define THRESH_TAP     0x1D   //Tap Threshold
#define OFSX           0x1E   //X-axis Offset
#define OFSY           0x1F   //Y-axis Offset
#define OFSZ           0x20   //Z-axis OffsetFF
#define DUR            0x21   //Tap duration
#define LATENT         0x22   //Tap latency
#define WINDOW         0x23   //Tap window
#define THRESH_ACT     0x24   //Activity threshold
#define THRESH_INACT   0x25   //Threshold inactivity
#define TIME_INACT     0x26   //Inactivity time
#define ACT_INACT_CTL  0x27   //Axis enable control for activity and inactivity detection
#define THRESH_FF      0x28   //Free-fall threshold
#define TIME_FF        0x29   //Free-fall time
#define TAP_AXES       0x2A   //Axis control for single tap/double tap
#define ACT_TAP_STATUS 0x2B   //Source of single tap/double tap
#define BW_RATE        0x2C   //Data rate and power mode control
#define POWER_CTL      0x2D   //Power-saving features control
#define INT_ENABLE     0x2E   //Interrupt enable control
#define INT_MAP        0x2F   //Interrupt mapping control
#define INT_SOURCE     0x30   //Source of interrupts
#define DATA_FORMAT    0x31   //Data format control
#define DATAX0         0x32   //X-axis Data 0
#define DATAX1         0x33   //X-axis Data 1
#define DATAY0         0x34   //Y-axis Data 0
#define DATAY1         0x35   //Y-axis Data 1
#define DATAZ0         0x36   //Z-axis Data 0
#define DATAZ1         0x37   //Z-axis Data 1
#define FIFO_CTL       0x38   //FIFO control
#define FIFO_STATUS    0x39   //FIFO status

short ADXL345::combineRegisters(unsigned char msb, unsigned char lsb){
   //shift the MSB left by 8 bits and OR with LSB
   return ((short)msb<<8)|(short)lsb;
}

void ADXL345::convertAccRawToGravity() {

	float gravity_range;
	switch(ADXL345::range){
		case ADXL345::PLUSMINUS_16_G:
			gravity_range=32.0f;
			break;
		case ADXL345::PLUSMINUS_8_G:
			gravity_range=16.0f;
			break;
		case ADXL345::PLUSMINUS_4_G:
			gravity_range=8.0f;
			break;
		default:
			gravity_range=4.0f;
			break;
	}
    float resolution = 1024.0f;
    if (this->resolution == ADXL345::HIGH)
    	resolution = 8192.0f;
    float factor = gravity_range/resolution;

    this->accX_G = this->accelerationX * factor;
    this->accY_G = this->accelerationY * factor;
    this->accZ_G = this->accelerationZ * factor;

}

void ADXL345::calculatePitchAndRoll(){
	float accXSquared = accX_G * accX_G ;
	float accYSquared = accY_G * accY_G ;
	float accZSquared = accZ_G * accZ_G ;
	this->pitch = 180 * atan(accX_G/sqrt(accYSquared + accZSquared))/M_PI;
	this->roll = 180 * atan(accY_G/sqrt(accXSquared + accZSquared))/M_PI;
}

int ADXL345::updateRegisters(){
   char data_format = 0x00;

   data_format = data_format|((this->resolution)<<3);
   data_format = data_format|this->range;
   return this->device->writeRegister(DATA_FORMAT, data_format);
}

ADXL345::ADXL345(BusDevice *busDevice) {
		this->device = busDevice;
		this->accelerationX = 0;
		this->accelerationY = 0;
		this->accelerationZ = 0;
		this->pitch = 0.0f;
		this->roll = 0.0f;
		this->registers = NULL;
		this->range = ADXL345::PLUSMINUS_16_G;
		this->resolution = ADXL345::HIGH;
		this->device->writeRegister(POWER_CTL, 0x08);
		this->updateRegisters();
}

int ADXL345::readSensorState(){
	this->registers = this->device->readRegisters(BUFFER_SIZE, 0x00);
	if(*this->registers != 0xe5){
		perror("ADXL345: Failure Condition - Sensor ID not Verified");
		return -1;
	}
	this->accelerationX = this->combineRegisters(*(registers + DATAX1), *(registers + DATAX0));
	this->accelerationY = this->combineRegisters(*(registers + DATAY1), *(registers + DATAY0));
	this->accelerationZ = this->combineRegisters(*(registers + DATAZ1), *(registers + DATAZ0));
	this->resolution = (ADXL345::RESOLUTION) (((*(registers + DATA_FORMAT)) & 0x08) >>3);
	this->range = (ADXL345::RANGE) ((*(registers+DATA_FORMAT)) & 0x03);
	this->convertAccRawToGravity();
	this->calculatePitchAndRoll();
	return 0;
}

void ADXL345::setRange(ADXL345::RANGE range) {
	this->range = range;
	updateRegisters();
}

void ADXL345::setResolution(ADXL345::RESOLUTION resolution) {
	this->resolution = resolution;
	updateRegisters();
}

void ADXL345::display(){
	while(1){
	      std::cout
		  << "	Pitch: " << this->getPitch()
		  << "  Roll: "  << this->getRoll()
		  << std::setprecision(2)
	      << "  ACC-X: " << this->getAccXGravity()
		  << "  ACC-Y: " << this->getAccYGravity()
		  << "  ACC-Z: " << this->getAccZGravity()
		  << "      \r"	 << std::flush;
	      usleep(100000);
	      this->readSensorState();
	}
}

ADXL345::~ADXL345() {}



#endif /* ADXL345_CPP_ */
