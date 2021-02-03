#include <iostream>
#include <cstdlib>
#include "SocketClient.h"

using namespace socketServerClient;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: ./client server_name port" << std::endl;
        std::cout << "Example: ./client 192.168.43.244 54321" << std::endl;
        return 2;
    }

    SocketClient sc(argv[1], atoi(argv[2]));
    sc.connectServer();

    std::string message("Hello Server side");
    sc.send(message);

    std::string receiver = sc.receive(1024);
    std::cout << "Receive:[ " << receiver << " ]" << std::endl;

    return 0;
}