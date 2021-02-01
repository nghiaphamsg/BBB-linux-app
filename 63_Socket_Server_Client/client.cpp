#include <iostream>
#include "include/SocketClient.h"

using namespace socketServerClient;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: ./client server_name" << std::endl;
        return 2;
    }

    SocketClient sc(argv[1], 54321);
    sc.connectServer();

    std::string message("Hello Server side");
    sc.send(message);

    std::string receiver = sc.receive(1024);
    std::cout << "Receive:[ " << receiver << " ]" << std::endl;

    return 0;
}