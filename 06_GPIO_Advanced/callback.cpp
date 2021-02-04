/*
 *  callback.cpp
 *
 *  Created on: Apr 14, 2020
 */

#include <iostream>
#include <unistd.h>
#include "inc/GPIO.h"

GPIO *outGPIO, *inGPIO;

int activateLED(int var)
{
   outGPIO->streamWrite(HIGH);
   std::cout << "Button Pressed" << std::endl;
   return 0;
}

int main()
{
   inGPIO = new GPIO(46);  // Button GPIO1_14 (P8_PIN16)
   outGPIO = new GPIO(60); // LED GPIO1_28 (P9_PIN12)

   inGPIO->setDirection(INPUT);
   outGPIO->setDirection(OUTPUT);
   outGPIO->streamOpen();
   outGPIO->streamWrite(LOW);
   inGPIO->setEdgeType(FALLING);

   std::cout << "You have 10 seconds to press the button now" << std::endl;
   inGPIO->waitForEdge(&activateLED);

   std::cout << "Listening, but also doing something else..." << std::endl;
   usleep(10000000); // Allow 10 seconds

   outGPIO->streamWrite(LOW);
   outGPIO->streamClose();

   return 0;
}
