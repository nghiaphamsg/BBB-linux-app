CC		= arm-linux-gnueabihf-gcc
CFLAGS	= -std=c11 -O0 -Wall -g
OBJS	= mpu6050Raw.o

mpu6050: $(OBJS)
	$(CC) -o mpu6050 $(OBJS)
mpu6050Raw.o: mpu6050Raw.c
	${CC} -c $< ${CFLAGS}

clean:
	@rm -f *.o mpu6050