all : controlLed_C
CC = arm-linux-gnueabihf-gcc
CFLAGS = -std=c11 -O0 -Wall -g
OBJS = controlLED.o

controlLed_C : $(OBJS)
	$(CC) -o controlLed_C $(OBJS)
	@chmod 777 controlLed_C
	@echo "Compile Success"
controlLED.o: controlLED.c 
	$(CC) -c controlLED.c $(CFLAGS)
clean:
	@if [ -f controlLed_C ] && [ -f $(OBJS) ]; \
	then \
		rm $(OBJS) controlLed_C; \
	elif [ -f $(OBJS) ]; \
	then \
		rm $(OBJS); \
	elif [ -f controlLed_C ]; \
	then \
		rm controlLed_C; \
	fi;
