#ifndef SOCKET_SERVER_H_
#define SOCKET_SERVER_H_

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <vector>
#include "ConnectionHandler.h"

namespace socketServerClient {
    class SocketServer
    {
    private:
        int serverSocketfd, clientSocketfd;
        int port;
        struct sockaddr_in serverAddr;
        struct sockaddr_in clientAddr;
        bool clientConnect;
        std::vector<ConnectionHandler *> connections;

    public:
        SocketServer(int port);
        virtual int listenClient();
        virtual int listenThreaded();
        virtual std::string receive(int size);
        virtual int send(std::string message);
        virtual void notifyThreadedDead(ConnectionHandler *connection);
        virtual ~SocketServer();
    };
   
}   /* namespace socketServerClient */

#endif  /* SOCKET_SERVER_H_ */
