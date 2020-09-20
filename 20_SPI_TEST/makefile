all: spitest
CC		= arm-linux-gnueabihf-gcc
CFLAGS	= -std=c11 -O0 -Wall -g
OBJS	= spitest.o

spitest: $(OBJS)
	$(CC) -o spitest $(OBJS)
spitest.o: spitest.c
	$(CC) -c $< $(CFLAGS)

clean:
	-@rm -f *.o spitest