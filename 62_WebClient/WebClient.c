/*
 * 	WebClient.c
 *  Created on: May 6, 2020
 */

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int socketfd, portNumber;
	struct sockaddr_in servAdd;
	struct hostent *server;

	char sendBuff[256];
	char recvBuff[2000];
	memset(sendBuff, 0, sizeof(sendBuff));
	memset(recvBuff, 0, sizeof(recvBuff));

	sprintf(sendBuff, "GET / HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", argv[1]);
	printf("Sending the message: %s", sendBuff);

	if (argc < 3)
	{
		printf("Incorrect usage, use: ./webBrowser hostname\n");
		return 2;
	}

	server = gethostbyname(argv[1]);
	if (server == NULL)
	{
		perror("Socket Client: error - unable to resolve host name.\n");
		return 1;
	}

	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd < 0)
	{
		perror("Socket Client: error opening TCP IP-based socket.\n");
		return 1;
	}

	memset((char *)&servAdd, 0, sizeof(servAdd));
	portNumber = atoi(argv[2]);

	servAdd.sin_family = AF_INET;
	servAdd.sin_port = htons(portNumber);

	/* Set the address to the resolved hostname address */
	memmove((char *)&servAdd.sin_addr.s_addr, (char *)server->h_addr, server->h_length);

	/* Connect to the server */
	if (connect(socketfd, (struct sockaddr *)&servAdd, sizeof(servAdd)) < 0)
	{
		perror("Socket Client: error connecting to the server.\n");
		return 1;
	}

	/* Send the HTTP request string	*/
	if (write(socketfd, sendBuff, sizeof(sendBuff)) < 0)
	{
		perror("Socket Client: error writing to socket");
		return 1;
	}

	/* Receive HTTP response to a maximum of 2000 characters */
	if (read(socketfd, recvBuff, sizeof(recvBuff)) < 0)
	{
		perror("Socket Client: error reading from socket");
		return 1;
	}

	/* Display the response */
	printf("**START**\n%s\n**END**\n", recvBuff);
	close(socketfd);
	return 0;
}