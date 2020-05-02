/*
 * ADXL345.h
 *
 *  Created on: May 3, 2020
 *  Author: NghiaPham
 */

#ifndef ADXL345_H_
#define ADXL345_H_


#include "BusDevice.h"

#define BUFFER_SIZE				0x40

class ADXL345{
	public:
		enum RANGE {
			PLUSMINUS_2_G 		= 0,
			PLUSMINUS_4_G 		= 1,
			PLUSMINUS_8_G 		= 2,
			PLUSMINUS_16_G 		= 3
		};
		enum RESOLUTION {
			NORMAL = 0,
			HIGH = 1
		};

	private:
		BusDevice *device;
		unsigned char *registers;
		ADXL345::RANGE range;
		ADXL345::RESOLUTION resolution;
		short accelerationX, accelerationY, accelerationZ;			// RAW value
		float accX_G, accY_G, accZ_G;								// Gravity value
		float pitch, roll;
		short combineRegisters(unsigned char msb, unsigned char lsb);
		virtual void convertAccRawToGravity();
		virtual void calculatePitchAndRoll();
		virtual int updateRegisters();
	public:
		ADXL345(BusDevice *busDevice);
		virtual int readSensorState();

		virtual void setRange(ADXL345::RANGE range);
		virtual ADXL345::RANGE getRange() {
			return this->range;
		}
		virtual void setResolution(ADXL345::RESOLUTION resolution);
		virtual ADXL345::RESOLUTION getResolution() {
			return this->resolution;
		}

		virtual short getAccelerationX() {
			return accelerationX;
		}
		virtual short getAccelerationY() {
			return accelerationY;
		}
		virtual short getAccelerationZ() {
			return accelerationZ;
		}
		virtual float getAccXGravity() {
			return accX_G;
		}
		virtual float getAccYGravity() {
			return accY_G;
		}
		virtual float getAccZGravity() {
			return accZ_G;
		}
		virtual float getPitch() {
			return pitch;
		}
		virtual float getRoll() {
			return roll;
		}

		virtual void display();
		virtual ~ADXL345();
};


#endif /* ADXL345_H_ */
