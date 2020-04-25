/*
 * 	ADXL345.h
 *
 *  Created on: Apr 25, 2020
 *  Author: NghiaPham
 */

#ifndef LIB_ADXL345_H_
#define LIB_ADXL345_H_

#include"I2C.h"

#define BUFFER_SIZE 0x40

/**
 * @class ADXL345
 * @brief Specific class for the ADXL345 Accelerometer that is a child of the I2CDevice class
 * Protected inheritance means that the public I2CDevice methods are not publicly accessible
 * by an object of the ADXL345 class.
 */
class ADXL345:protected I2C{
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
		unsigned int I2CBus, I2CAddress;
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
		ADXL345(unsigned int I2CBus, unsigned int I2CAddress=0x53);
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

#endif /* LIB_ADXL345_H_ */
