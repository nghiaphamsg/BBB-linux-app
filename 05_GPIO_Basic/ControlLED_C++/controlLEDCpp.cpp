/*
 ============================================================================
 Name        : ControlLED.cpp
 Author      : NghiaPham
 Version     : v0.1
 Copyright   : Your copyright notice
 Description : Control USER LED 0, 1, 2, 3 (internal Led) in BBB, write by cpp
 ============================================================================
 */


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define PATH "/sys/class/leds/beaglebone:green:usr"

class LED
{
private:
	int pinNumber;
	std::string statePath;
	virtual void writeStateLED(std::string fileName, std::string value);

public:
	LED(int number);
	virtual void removeTrigger();
	virtual void turnOnLED();
	virtual void turnOffLED();
	virtual void flashLED(std::string delayms);
	virtual ~LED();
};

LED::LED(int number)
	: pinNumber{number}
{
	std::ostringstream s;
	s << PATH << pinNumber;
	statePath = std::string(s.str());
}

void LED::writeStateLED(std::string fileName, std::string value)
{
	std::ofstream fs;
	fs.open((statePath + fileName).c_str());
	fs << value;
	fs.close();
}

void LED::removeTrigger()
{
	writeStateLED("/trigger", "none");
}

void LED::turnOnLED()
{
	std::cout << "Turning LED " << pinNumber << " on." << std::endl;
	writeStateLED("/brightness", "1");
}

void LED::turnOffLED()
{
	std::cout << "Turning LED " << pinNumber << " off." << std::endl;
	writeStateLED("/brightness", "0");
}

void LED::flashLED(std::string delayms = "50")
{
	std::cout << "Making LED " << pinNumber << " flash." << std::endl;
	writeStateLED("/trigger", "timer");
	writeStateLED("/delay_on", delayms);
	writeStateLED("/delay_off", delayms);
}

LED::~LED()
{
	std::cout << "Destroying the LED with path: " << statePath << std::endl;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "	Usage: " << argv[0] << " <command>" << std::endl;
		std::cout << "	command is one of: <on> <off> or <flash>" << std::endl;
		std::cout << "	e.g. makeLEDs flash" << std::endl;
	}

	std::cout << "Starting the makeLEDs program" << std::endl;
	std::string cmd{argv[1]};
	LED leds[4] = {LED(0), LED(1), LED(2), LED(3)};
	for (int i = 0; i <= 3; i++)
	{
		if (cmd == "on")
		{
			leds[i].removeTrigger();
			leds[i].turnOnLED();
		}
		else if (cmd == "off")
			leds[i].turnOffLED();
		else if (cmd == "flash")
			leds[i].flashLED("150");
		else
			std::cout << "Invalid command!" << std::endl;
	}
	std::cout << "Finished the makeLEDs program" << std::endl;
	return 0;
}
