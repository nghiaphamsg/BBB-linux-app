all: mpu6050
CXX		= arm-linux-gnueabihf-g++
CFLAGS	= -std=c++17 -O0 -Wall -g
INCLUDE	= ./inc

OBJS	= MPU6050_I2C.o ./inc/MPU6050.o ./inc/I2C.o 

mpu6050: $(OBJS)
	$(CXX) -o mpu6050 $(OBJS) $(LIBS)
MPU6050_I2C.o: MPU6050_I2C.cpp ./inc/MPU6050.h
	$(CXX) -c $< $(CFLAGS) -I $(INCLUDE)

include: ./inc/makefile

clean:
	-@rm -f *.o mpu6050
	-@rm -f inc/*.o