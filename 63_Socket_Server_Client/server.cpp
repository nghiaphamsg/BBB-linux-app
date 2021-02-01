#include <iostream>
#include "SocketServer.h"

using namespace socketServerClient;

int main(int argc, char *argv[])
{
    SocketServer ss(54321);
    ss.listenClient();

    std::string receive = ss.receive(1024);
    std::cout << "Receive: [ " << receive << " ]" << std::endl;

    std::string send("Hi Client side!!!");
    ss.send(send);

    return 0;
}