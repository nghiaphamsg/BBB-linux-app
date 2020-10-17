CXX		= arm-linux-gnueabihf-g++
CFLAGS	= -std=c++17 -O0 -Wall -g
INCLUDE	= .

OBJS	= webclient.o ./inc/SocketClient.o

webclient: $(OBJS)
	$(CXX) -o webclient $(OBJS)
webclient.o: webclient.cpp ./inc/SocketClient.h
	$(CXX) -c $< $(CFLAGS) -I $(INCLUDE)

include: ./inc/makefile

clean:
	-@rm -f *.o webclient
	-@rm -f inc/*.o