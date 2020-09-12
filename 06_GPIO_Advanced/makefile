all: poll callback
CXX		= arm-linux-gnueabihf-g++
CFLAGS	= -std=c++17 -O0 -Wall -g
LIBS	= -pthread
INCLUDE	= .

OBJS	= poll.o ./inc/GPIO.o
OBJS2	= callback.o ./inc/GPIO.o

poll: $(OBJS)
	$(CXX) -o poll $(OBJS) $(LIBS)
callback: $(OBJS2)
	$(CXX) -o callback $(OBJS2) $(LIBS)
poll.o: poll.cpp ./inc/GPIO.h
	$(CXX) -c $< $(CFLAGS) -I $(INCLUDE)
callback.o: callback.cpp ./inc/GPIO.h
	$(CXX) -c $< $(CFLAGS) -I $(INCLUDE)

include: ./inc/makefile

clean:
	-@rm -f *.o poll callback
	-@rm -f inc/*.o