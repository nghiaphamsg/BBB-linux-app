#include <iostream>
#include <unistd.h>
#include "ConnectionHandler.h"
#include "SocketServer.h"

namespace socketServerClient {
    ConnectionHandler::ConnectionHandler(SocketServer *parent, sockaddr_in *client, int clientSockFd)
    {
        this->parent = parent;
        this->client = client;
        this->clientSockFd = clientSockFd;
        this->running = true;
    }

    int ConnectionHandler::createThread()
    {
        if (pthread_create(&thread, NULL, threadH, this) != 0)
        {
            std::cout << "Thread: create thread failed" << std::endl;
            return -1;
        }
        return 0;
    }

    void ConnectionHandler::waitThread()
    {
        static_cast<void>(pthread_join(thread, NULL));
    }

    int ConnectionHandler::send(std::string message)
    {
        const char *buff = message.data();
        int length = message.length();
        if (write(clientSockFd, buff, length) < 0)
        {
            std::cout << "Socket Server: error writing to server socket" << std::endl;
            return 1;
        }
        return 0;
    }

    std::string ConnectionHandler::receive(int size)
    {
        char readbuff[size];
        if (read(clientSockFd, readbuff, sizeof(readbuff)) < 0)
        {
            std::cout << "Socket Server: error reading from server socket" << std::endl;
        }
        return std::string(readbuff);
    }

    void ConnectionHandler::threadLoop()
    {
        while (running)
        {
            std::string rec;
            std::string mess("Server with thread feedback");

            rec = receive(1024);
            std::cout << "Receive: " << rec << std::endl;

            usleep(5000000);
            send(mess);
            running = false;
        }
        parent->notifyThreadedDead(this);
    }

    ConnectionHandler::~ConnectionHandler()
    {
        this->running = false;
        delete client;
    }
}