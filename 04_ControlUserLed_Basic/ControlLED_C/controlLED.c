/*
 ============================================================================
 Name        : ControlLED.c
 Author      : NghiaPham
 Version     : v0.1
 Copyright   : Your copyright notice
 Description : Control USER LED 3 (internal Led) in BBB, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#define SYS_FS_LEDS_PATH 		"/sys/class/leds"
#define USR_LED_NUMBER 			3
#define BUFF_BYTES 				200

int writeBrightness(uint8_t ledNum, char *state) {
	int fd, ret;
	char buf[BUFF_BYTES];

	snprintf(buf, sizeof(buf), SYS_FS_LEDS_PATH "/beaglebone:green:usr%d/brightness", ledNum);
	fd = open(buf, O_WRONLY);
	if(fd < 0) {
		perror("Write brightness error \n");
		return -1;
	}
	ret = write(fd, (void*)state, sizeof(state));
	if (ret <= 0) {
		printf("Brightness value write error \n");
		return -1;
	}
	return EXIT_SUCCESS;
}

int writeTrigger(uint8_t ledNum, char *state) {
	int fs, ret = 0;
	char buff[BUFF_BYTES];

	snprintf(buff, sizeof(buff), SYS_FS_LEDS_PATH "/beaglebone:green:usr%d/trigger", ledNum);

	fs = open(buff, O_WRONLY);
	if(fs < 0) {
		perror("Write trigger error \n");
		return -1;
	}

	ret = write(fs, (void*)state, strlen(state));
	if (ret <= 0) {
		printf("Trigger value write error \n");
		return -1;
	}
	return EXIT_SUCCESS;
}

void processBrightness(char *state) {
	if (!(strcmp(state, "0") && strcmp(state, "1"))){
		writeBrightness(USR_LED_NUMBER, state);
	}
	else {
		printf("Invalid value \n");
		printf("Valid brightness values : 0 or 1 \n");
	}
}

void processTrigger(char *state) {
	if (!(strcmp(state, "timer") && strcmp(state, "heartbeat") && \
		strcmp(state, "none") && strcmp(state, "shot") && \
		strcmp(state, "default-on"))){
		writeTrigger(USR_LED_NUMBER, state);
	}
	else {
		printf("Invalid value \n");
		printf("Valid trigger values: heartbeat, timer, none, oneshot, default-on \n");
	}
}

int main(int argc, char *argv[]) {
	printf("This Application controls the USER LED3\n");

	if(argc != 3) {
        printf("Usage: %s <option> <state> \n", argv[0] );
        printf("Valid 'option': <brightness> <trigger> \n");
        printf("	- brightness: <0> <1> \n");
        printf("	- trigger: <heartbeat> <timer> <none> <shot> <default-on> \n");
	}

	if(strcmp(argv[1], "brightness") == 0) {
		processBrightness(argv[2]);
	}
	else if(strcmp(argv[1], "trigger") == 0) {
		processTrigger(argv[2]);
	}
	else {
		printf("Invalid control option \n");
		printf("Valid control_options : brightness, trigger \n");
	}

	return EXIT_SUCCESS;
}
