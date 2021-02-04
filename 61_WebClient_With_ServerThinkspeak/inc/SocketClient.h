/*
 *  SocketClient.h
 *  Created on: May 7, 2020
 */

#ifndef SOCKETCLIENT_H_
#define SOCKETCLIENT_H_

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include "string"

class SocketClient
{
private:
	int socketfd, portNumber;
	struct sockaddr_in servAdd;
	struct hostent *server;
	std::string serverName;
	bool isConnected;

public:
	SocketClient(std::string serverName, int portNumber);
	virtual int connectServer();
	virtual int disconnectServer();
	virtual int send(std::string msg);
	virtual std::string receive(int size);
	bool isClientConnect() { return isConnected; }
	virtual ~SocketClient();
};

#endif /* SOCKETCLIENT_H_ */