/*
 *  PressButtonAndToggleGPIO.cpp
 *
 *  Created on: Apr 15, 2020
 *  Author: NghiaPham
 */

#include <iostream>
#include <unistd.h>
#include "GPIO.h"

GPIO *outGPIO, *inGPIO;

int callBackFunction(int var) {
	std::cout << "Button Pressed" << std::endl;
	std::cout << "<<<DEBUG>>> GPIO(48) has value: " << inGPIO->getValue() << std::endl;
	return var;
}

int main() {
   inGPIO = new GPIO(46);         							// Button GPIO1_14 (P8_PIN16)
   outGPIO = new GPIO(60);									   // LED	 GPIO1_28 (P9_PIN12)

   inGPIO->setDirection(INPUT);
   inGPIO->setEdgeType(RISING);
   outGPIO->setDirection(OUTPUT);

   std::cout << "GPIO(48) has value: " << inGPIO->getValue() << std::endl;
   
   inGPIO->setDebounceTime(200);
   inGPIO->waitForEdge(&callBackFunction);
   outGPIO->toggleOutput(1000);								// 0.5 second toggle (500*1000)

   std::cout << "Poll Started: Press the button:" << std::endl;
   usleep(10000000);

   outGPIO->streamWrite(LOW);
   outGPIO->streamClose();
   std::cout << "Finished sleeping for 10 seconds" << std::endl;

   return 0;
}
