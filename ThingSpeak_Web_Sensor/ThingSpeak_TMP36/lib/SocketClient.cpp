/*
 * SocketClient.cpp
 *
 *  Created on: May 7, 2020
 *  Author: NghiaPham
 */

#include "SocketClient.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

SocketClient::SocketClient(std::string serverName, int portNumber) {
   this->socketfd = -1;
   this->server = NULL;
   this->serverName = serverName;
   this->portNumber = portNumber;
   this->isConnected = false;
}


int SocketClient::connectServer(){
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if(socketfd < 0) {
    	perror("Socket Client: error opening socket.\n");
    	return 1;
    }

    server = gethostbyname(serverName.data());
    if(server == NULL) {
        perror("Socket Client: error - no such host.\n");
        return 1;
    }
    memset((char *)&servAdd, 0, sizeof(servAdd));
    servAdd.sin_family = AF_INET;
    memmove((char *)&servAdd.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
    servAdd.sin_port = htons(portNumber);

    if (connect(socketfd, (struct sockaddr *) &servAdd, sizeof(servAdd)) < 0){
    	perror("Socket Client: error connecting to the server.\n");
    	return 1;
    }
    isConnected = true;
    return 0;
}

int SocketClient::send(std::string msg){
   const char *writeBuffer = msg.data();
   int length = msg.length();
   if ((write(this->socketfd, writeBuffer, length))< 0){
      perror("Socket Client: error writing to socket");
      return 1;
   }
   return 0;
}

std::string SocketClient::receive(int size = 1024){
    char readBuffer[size];
    if ((read(this->socketfd, readBuffer, sizeof(readBuffer))) < 0){
       perror("Socket Client: error reading from socket");
    }
    return std::string(readBuffer);
}

int SocketClient::disconnectServer(){
   isConnected = false;
   close(socketfd);
   return 0;
}

SocketClient::~SocketClient() {
   if (isConnected == true){
      disconnectServer();
   }
}
