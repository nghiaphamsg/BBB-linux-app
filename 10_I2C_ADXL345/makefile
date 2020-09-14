all: adxl345
CXX		= arm-linux-gnueabihf-g++
CFLAGS	= -std=c++17 -O0 -Wall -g
INCLUDE	= ./inc

OBJS	= ADXL345_I2C.o ./inc/ADXL345.o ./inc/I2C.o 

adxl345: $(OBJS)
	$(CXX) -o adxl345 $(OBJS) $(LIBS)
ADXL345_I2C.o: ADXL345_I2C.cpp ./inc/ADXL345.h
	$(CXX) -c $< $(CFLAGS) -I $(INCLUDE)

include: ./inc/makefile

clean:
	-@rm -f *.o adxl345
	-@rm -f inc/*.o