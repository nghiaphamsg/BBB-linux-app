all : rtcds3231
CC = arm-linux-gnueabihf-gcc
CFLAGS = -std=c11 -O0 -Wall -g
OBJS = rtcds3231.o

rtcds3231 : $(OBJS)
	$(CC) -o rtcds3231 $(OBJS)
rtcds3231.o: rtcds3231.c 
	$(CC) -c rtcds3231.c $(CFLAGS)
clean:
	@rm -f *.o rtcds3231
