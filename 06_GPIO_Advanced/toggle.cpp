/*
 *  toggle.cpp
 *
 *  Created on: Apr 15, 2020 Author: NghiaPham
 */

#include <iostream>
#include <unistd.h>
#include "inc/GPIO.h"

GPIO *outGPIO, *inGPIO;
int count = 1;

int callBackFunction(int var) {
	std::cout << "Pressed button " << count++ << " times" <<std::endl;
	std::cout << "------------------------------" << std::endl;
	return var;
}

int main() {
    inGPIO = new GPIO(46);         							// Button GPIO1_14 (P8_PIN16)
    outGPIO = new GPIO(60);								    // LED	 GPIO1_28 (P9_PIN12)

    inGPIO->setDirection(INPUT);
    inGPIO->setEdgeType(RISING);
    outGPIO->setDirection(OUTPUT);

    std::cout << "Press button event & toggle led starting..." << std::endl;
    inGPIO->setDebounceTime(200);
    inGPIO->waitForEdge(&callBackFunction);
    outGPIO->toggleOutput(500);						        // 0.5 second toggle (500*1000)
    while(1) {}
    return 0;
}
