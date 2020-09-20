all: 74hc595
CC		= arm-linux-gnueabihf-gcc
CFLAGS	= -std=c11 -O0 -Wall -g
OBJS	= 74HC595_SPI.o

74hc595: $(OBJS)
	$(CC) -o 74hc595 $(OBJS) $(LIBS)
74HC595_SPI.o: 74HC595_SPI.c
	$(CC) -c $< $(CFLAGS)

clean:
	-@rm -f *.o 74hc595