/*
 *  PressButtonAndToggleGPIO.cpp
 *
 *  Created on: Apr 15, 2020 Author: NghiaPham
 */

#include <iostream>
#include <unistd.h>
#include "inc/GPIO.h"

GPIO *outGPIO, *inGPIO;

int main() {
   inGPIO = new GPIO(46);         							// Button GPIO1_14 (P8_PIN16)
   outGPIO = new GPIO(60);									   // LED	 GPIO1_28 (P9_PIN12)

   inGPIO->setDirection(INPUT);
   inGPIO->setEdgeType(FALLING);
   outGPIO->setDirection(OUTPUT);

   outGPIO->streamOpen();
   outGPIO->streamWrite(LOW);
   std::cout << "Press the button:" << std::endl;
   inGPIO->waitForEdge();
   outGPIO->streamWrite(HIGH);
   outGPIO->streamClose();
   return 0;
}
