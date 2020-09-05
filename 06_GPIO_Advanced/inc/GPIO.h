/*
 * 	GPIO.h
 *
 *  Created on: Apr 13, 2020
 *  Author: NghiaPham
 */

#ifndef GPIO_H_
#define GPIO_H_


#include <string>
#include <fstream>

#define GPIO_PATH 		"/sys/class/gpio/"

typedef int (*callBackType)(int);

enum GPIO_DIRECTION {
	INPUT,
	OUTPUT
};

enum GPIO_VALUE {
	LOW = 0,
	HIGH = 1
};

enum GPIO_EDGE {
	NONE,
	RISING,
	FALLING,
	BOTH
};


class GPIO {
	private:
		int number, debounceTime;
		std::string name, path;
		int togglePeriod;
		int toggleNumber;
		bool threadRunning;
		std::ofstream stream;
		callBackType callBackFunction;
		int write(std::string path, std::string fileName, std::string value);
		int write(std::string path, std::string fileName, int value);
		std::string read(std::string path, std::string fileName);
		friend void* threadedToggle(void* value);
		friend void* threadedPoll(void* value);
	public:
		GPIO(int number);
		virtual int getPinNumber() {
			return number;
		}

		/* General Input and Output Settings */
		virtual int setDirection(GPIO_DIRECTION);
		virtual GPIO_DIRECTION getDirection();
		virtual int setValue(GPIO_VALUE);
		virtual GPIO_VALUE getValue();
		virtual int setActiveLow(bool isLow = true);
		virtual int setActiveHigh();
		virtual void setDebounceTime(int time) {
			this->debounceTime = time;
		}

		/* Advanced OUTPUT: Faster write by keeping the stream alive (~20X) */
		virtual int streamOpen();
		virtual int streamWrite(GPIO_VALUE);
		virtual int streamClose();

		virtual int toggleOutput();
		virtual int toggleOutput(int time);
		virtual int toggleOutput(int numberOfTimes, int time);
		virtual void changeToggleTime(int time) {
			this->togglePeriod = time;
		}
		virtual void toggleCancel() {
			this->threadRunning = false;
		}

		/* Advanced INPUT: Detect input edges; threaded and non-threaded */
		virtual int setEdgeType(GPIO_EDGE);
		virtual GPIO_EDGE getEdgeType();
		virtual int waitForEdge();
		virtual int waitForEdge(callBackType callback);
		virtual void waitForEdgeCancel() {
			this->threadRunning = false;
		}

		virtual ~GPIO();
};

void* threadedToggle(void *value);
void* threadedPoll(void* value);
#endif /* GPIO_H_ */
