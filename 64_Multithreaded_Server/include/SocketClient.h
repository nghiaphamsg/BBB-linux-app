#ifndef SOCKETCLIENT_H_
#define SOCKETCLIENT_H_

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace socketServerClient {
    class SocketClient {
    private:
        int socketfd, portNumber;
        struct sockaddr_in servAdd;
        struct hostent *server;
        std::string serverName;
        bool isConnected;
        const char *ipaddr;
    public:
        SocketClient(std::string serverName, int portNumber);
        virtual int connectServer();
        virtual int disconnectServer();
        virtual int send(std::string msg);
        virtual std::string receive(int size);
        bool isClientConnect() {
            return isConnected;
        }
        virtual ~SocketClient();
    };
}   /* namespace socketServerClient */

#endif /* SOCKETCLIENT_H_ */