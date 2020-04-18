//============================================================================
// Name        : GPIO.cpp
// Author      : NghiaPham
// Version     : v0.1
// Copyright   : Your copyright notice
// Description : Press Button With Call Back Function in C++,
//				 When press button turn on or turn off external LED
//============================================================================

#include "GPIO.h"
#include <iostream>
#include <string>
#include <fstream>
#include <pthread.h>
#include <stdlib.h>
#include <sstream>
#include <unistd.h>
#include <sys/epoll.h>
#include <cstdio>
#include <fcntl.h>

GPIO::GPIO(int number) {
	this->number = number;
	this->debounceTime = 0;
	this->togglePeriod = 100;
	this->toggleNumber = -1; //infinite number
	this->callBackFunction = NULL;
	this->threadRunning = false;
	std::ostringstream s;
	s << "gpio" << number;
	this->name = std::string(s.str());
	this->path = GPIO_PATH + this->name + "/";
	usleep(250000); 							//delay 250ms
};


int GPIO::write(std::string path, std::string fileName, std::string value) {
	std::ofstream fs;

	fs.open((path + fileName).c_str());
	if(!fs.is_open()) {
		std::perror("<<<DEBUG>>> GPIO: write failed to open file");
		return -1;
	}
	fs << value;
	fs.close();
	return 0;
}

int GPIO::write(std::string path, std::string fileName, int value) {
	std::stringstream s;
	s << value;
	return write(path, fileName, s.str());
}

std::string GPIO::read(std::string path, std::string fileName) {
	std::ifstream fs;

	fs.open((path + fileName).c_str());
	if(!fs.is_open()) {
		std::perror("<<<DEBUG>>> GPIO: read failed to open file");
	}
	std::string input;
	std::getline(fs, input);
	fs.close();
	return input;
}

int GPIO::setDirection(GPIO_DIRECTION dir) {
	switch (dir) {
		case INPUT:
			return this->write(path, "direction", "in");
			break;
		case OUTPUT:
			return this->write(path, "direction", "out");
			break;
	}
	return -1;
}

int GPIO::setValue(GPIO_VALUE val) {
	switch (val) {
		case LOW:
			return write(path, "value", "0");
			break;
		case HIGH:
			return write(path, "value", "1");
			break;
	}
	return -1;
}
int GPIO::setEdgeType(GPIO_EDGE state) {
	switch (state) {
		case NONE:
			return write(path, "edge", "none");
			break;
		case RISING:
			return write(path, "edge", "rising");
			break;
		case FALLING:
			return write(path, "edge", "falling");
			break;
		case BOTH:
			return write(path, "edge", "both");
			break;
	}
	return -1;
}

int GPIO::setActiveLow(bool isLow) {
	if(isLow)
		return write(path, "active_low", "1");
	else
		return write(path, "active_low", "0");
}

int GPIO::setActiveHigh() {
	return setActiveLow(false);
}

GPIO_DIRECTION GPIO::getDirection() {
	std::string input;
	input = read(path, "direction");
	if(input == "in")
		return INPUT;
	return OUTPUT;
}

GPIO_VALUE GPIO::getValue() {
	std::string input;
	input = read(path, "value");
	if(input == "0")
		return LOW;
	return HIGH;
}

GPIO_EDGE GPIO::getEdgeType() {
	std::string input;
	input = read(path, "edge");
	if(input == "none")
		return NONE;
	else if(input == "rising")
		return RISING;
	else if(input == "falling")
		return FALLING;
	return BOTH;
}

int GPIO::streamOpen() {
	stream.open((path + "value").c_str());
	return 0;
}

int GPIO::streamWrite(GPIO_VALUE val) {
	stream << val << std::flush;
	return 0;
}

int GPIO::streamClose(){
	stream.close();
	return 0;
}

int GPIO::toggleOutput() {
	setDirection(OUTPUT);
	if((bool)getValue())
		return setValue(LOW);
	else
		return setValue(HIGH);
	return 0;
}

int GPIO::toggleOutput(int time) {
	return toggleOutput(-1, time);
}

int GPIO::toggleOutput(int numberOfTimes, int time) {
	setDirection(OUTPUT);
	toggleNumber = numberOfTimes;
	togglePeriod  = time;
	threadRunning = true;
	pthread_t thread;
	if(pthread_create(&thread, NULL, &threadedToggle, static_cast<void*>(this))) {
		perror("<<<DEBUG>>> GPIO: Failed to create the toggle thread");
		threadRunning = false;
		return -1;
	}
	return 0;
}

void* threadedToggle(void* value) {
	GPIO *gpio = static_cast<GPIO*>(value);
	bool isHigh = gpio->getValue();
	while(gpio->threadRunning) {
		if(isHigh)
			gpio->setValue(HIGH);
		else
			gpio->setValue(LOW);
		usleep(gpio->togglePeriod * 500);
		isHigh =! isHigh;
		if(gpio->toggleNumber > 0)
			gpio->toggleNumber--;
		if(gpio->toggleNumber == 0)
			gpio->threadRunning = false;
	}
	return 0;
}

// Blocking Poll
int GPIO::waitForEdge() {
	setDirection(INPUT);
	int fd, i, epollfd, count=0;
	struct epoll_event ev;
	epollfd = epoll_create(1);

	if(epollfd == -1) {
	   perror("<<<DEBUG>>> GPIO: Failed to create epollfd");
	   return -1;
	}

	fd = open((this->path + "value").c_str(), O_RDONLY | O_NONBLOCK);
    if(fd == -1) {
       perror("<<<DEBUG>>> GPIO: Failed to open file");
       return -1;
    }

    // ev.events = read operation | edge triggered | urgent data
    ev.events = EPOLLIN | EPOLLET | EPOLLPRI;
    ev.data.fd = fd;  						// Attach the file file descriptor

    //Register the file descriptor on the epoll instance
    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev) == -1) {
       perror("<<<DEBUG>>> GPIO: Failed to add control interface");
       return -1;
    }
	while(count <= 1){  					// Ignore the first trigger
		i = epoll_wait(epollfd, &ev, 1, -1);
		if(i == -1){
			perror("<<<DEBUG>>> GPIO: Poll Wait fail");
			count = 5; 						// Terminate loop
		}
		else {
			count++; 						// Count the triggers up
		}
	}
    close(fd);
    if(count == 5) {
    	return -1;
    }
	return 0;
}

void* threadedPoll(void* value) {
	GPIO *gpio = static_cast<GPIO*>(value);
	while(gpio->threadRunning) {
		gpio->callBackFunction(gpio->waitForEdge());
		usleep(gpio->debounceTime * 1000);
	}
	return 0;
}

int GPIO::waitForEdge(callBackType callback){
	this->threadRunning = true;
	this->callBackFunction = callback;
	pthread_t thread;
    // Create the thread, pass the reference, address of the function and data
    if(pthread_create(&thread, NULL, &threadedPoll, static_cast<void*>(this))){
    	perror("<<<DEBUG>>> GPIO: Failed to create the poll thread");
    	this->threadRunning = false;
    	return -1;
    }
    return 0;
}

GPIO::~GPIO() {}
