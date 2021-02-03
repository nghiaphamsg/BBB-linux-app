#include "SocketClient.h"
#include <string.h>
#include <string>

namespace socketServerClient {
    SocketClient::SocketClient(std::string serverName, int portNumber)
    {
        this->socketfd = -1;
        this->server = NULL;
        this->serverName = serverName;
        this->portNumber = portNumber;
        this->isConnected = false;
        this->ipaddr = NULL;
    }

    int SocketClient::connectServer()
    {

        socketfd = socket(AF_INET, SOCK_STREAM, 0);
        if(socketfd < 0)
        {
            std::cout << "Socket Client: error opening socket" << std::endl;
            return 1;
        }

        server = gethostbyname(serverName.data());
        if(server == NULL)
        {
            std::cout << "Socket Client: error - no such host" << std::endl;
            return 1;
        }

        memset((char *)&servAdd, 0, sizeof(servAdd));
        servAdd.sin_family = AF_INET;
        servAdd.sin_port = htons(portNumber);
        ipaddr = inet_ntoa(*((struct in_addr *)server->h_addr));
        inet_aton(ipaddr, &servAdd.sin_addr);

        if (connect(socketfd, (struct sockaddr *) &servAdd, sizeof(servAdd)) < 0)
        {
            std::cout << "Socket Client: error connecting to the server" << std::endl; 
            return 1;
        }

        isConnected = true;
        return 0;
    }

    int SocketClient::send(std::string msg)
    {
        const char *writeBuffer = msg.data();
        int length = msg.length();

        if ((write(socketfd, writeBuffer, length))< 0)
        {
            std::cout << "Socket Client: error writing to socket" << std::endl;
            return 1;
        }
        return 0;
    }

    std::string SocketClient::receive(int size = 1024)
    {
        char readBuffer[size];
        if ((read(socketfd, readBuffer, sizeof(readBuffer))) < 0)
        {
            std::cout << "Socket Client: error reading from socket" << std::endl;
        }
        return std::string(readBuffer);
    }

    int SocketClient::disconnectServer()
    {
        isConnected = false;
        close(socketfd);
        return 0;
    }

    SocketClient::~SocketClient()
    {
        if (isConnected == true)
            disconnectServer();
    }

}   /* namespace socketServerClient */