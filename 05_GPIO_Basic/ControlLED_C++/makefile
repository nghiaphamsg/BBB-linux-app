all : controlLed_Cpp
CC = arm-linux-gnueabihf-g++
CFLAGS = -std=c++11 -O0 -Wall -g
OBJS = controlLEDCpp.o

controlLed_Cpp : $(OBJS)
	$(CC) -o controlLed_Cpp $(OBJS)
	@chmod 777 controlLed_Cpp
	@echo "Compile Success"
controlLEDCpp.o: controlLEDCpp.cpp
	$(CC) -c controlLEDCpp.cpp $(CFLAGS)
clean:
	@if [ -f controlLed_Cpp ] && [ -f $(OBJS) ]; \
	then \
		rm $(OBJS) controlLed_Cpp; \
	elif [ -f $(OBJS) ]; \
	then \
		rm $(OBJS); \
	elif [ -f controlLed_Cpp ]; \
	then \
		rm controlLed_Cpp; \
	fi;
