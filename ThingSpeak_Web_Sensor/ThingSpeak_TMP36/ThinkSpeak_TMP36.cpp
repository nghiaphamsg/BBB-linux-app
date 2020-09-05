/*
 * ThinkSpeak_TMP36.cpp
 *
 *  Created on: May 7, 2020
 *  Author: NghiaPham
 */

#include "SocketClient.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "string.h"
#include <unistd.h>

#define ADC					0
#define ADC_PATH			"/sys/bus/iio/devices/iio:device0/in_voltage"
#define TEMP_EXCEEDED 		25

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

int sendMail() {
	std::string to = "chyngia@gmail.com";
	std::string subject = "Temperature Notification";
	std::ostringstream body;
	std::ostringstream command;

	body << "Temperature exceeded " << TEMP_EXCEEDED << " degrees C";
	command << "echo \""<< body.str() <<"\" | mail -s \""<< subject <<"\" "<< to;

	int result = system(command.str().c_str());
	std::cout << "Command: " << command.str() << std::endl;
	std::cout << "The return value was " << result << std::endl;

	return result;
}

int main() {
	float getTemp;
	getTemp = getTemperature(readAnalog(ADC));

	std::ostringstream head, data;
	std::cout << "Starting ThingSpeak Example" << std::endl;

	SocketClient sc("api.thingspeak.com",80);
	data << "field1=" << getTemp << std::endl;
	sc.connectServer();

	/* HTTP Form Request message */
	head << "POST /update HTTP/1.1\n"
		 << "Host: api.thingspeak.com\n"
		 << "Connection: Keep-Alive\n"
		 << "Accept-Language: en-us\n"
		 << "X-THINGSPEAKAPIKEY: Z78U9SGFHDD1LPUA\n"
		 << "Content-Type: application/x-www-form-urlencoded\n"
		 << "Content-Length:" << std::string(data.str()).length() << "\n\n";

	sc.send(std::string(head.str()));
	sc.send(std::string(data.str()));
	std::string rec = sc.receive(2000);

	std::cout << "[" << rec << "]" << std::endl;
	std::cout << "End of ThingSpeak Example" << std::endl;

	if(getTemp >= TEMP_EXCEEDED) {
		if(sendMail() != 0) {
			perror("Send mail fail");
			return -1;
		}
	}
}
