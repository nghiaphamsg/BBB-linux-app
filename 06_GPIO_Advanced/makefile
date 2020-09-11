all:	gpio
CC		= arm-linux-gnueabihf-g++
CFLAGS	= -std=c++11 -O0 -Wall -g
LIBS	= -pthread
OBJS	= PressButtonAndToggleGPIO.o ./inc/GPIO.o
OBJS2	= callBackFuncWithThread.o ./inc/GPIO.o

gpio: $(OBJS) $(OBJS2)
	$(CC) -o poll $(OBJS) $(LIBS)
	$(CC) -o callback $(OBJS2) $(LIBS)
PressButtonAndToggleGPIO.o: PressButtonAndToggleGPIO.cpp ./inc/GPIO.h
	$(CC) -c $< $(CFLAGS)
callBackFuncWithThread.o: callBackFuncWithThread.cpp ./inc/GPIO.h
	$(CC) -c $< $(CFLAGS)

include: ./inc/makefile

clean:
	-@rm -f *.o poll callback
	-@rm -f inc/*.o