/* 
 *  @brief: Web client with secure communication using OpenSSL
 *  @data: 2021/02/01
 *  @package: sudo apt-get install openssl libssl-dev
 *  @usage: g++ webClientSSL.cpp -o webClientSSL -lcrypto -lssl
 *          ./webClientSSL www.google.com
*/

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <openssl/ssl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int sockfd, result;
    const char *ipaddr;
    int port = 443;
    char mess[255], buff[3000]; 
    struct sockaddr_in dest_addr;
    struct hostent *host;

    if (argc <= 1 || argv[1] == "help"){
        std::cout << "Incorrect usage, use: ./webClientSSL hostname" << std::endl;
        return 2;
    }

    sprintf(mess, "GET / HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", argv[1]);

    host = gethostbyname(argv[1]);
    if (host == nullptr)
    {
        std::cout << "Socket Client: error - unable to resolve host name" << std::endl;
        return 1;
    }

    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        std::cout << "Socket Client: error opening TCP IP-based socket" << std::endl;
        return 1;
    }

    /* Set the server IP, port,.. */
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port);
    ipaddr = inet_ntoa(*((struct in_addr *)host->h_addr));
    inet_aton(ipaddr, &dest_addr.sin_addr);
    memset(&(dest_addr.sin_zero), 0, sizeof dest_addr.sin_zero);

    result = connect(sockfd, (struct sockaddr *)&dest_addr, sizeof dest_addr);
    if (result < 0)
    {
        std::cout << "Socket Client: error connecting to the server" << std::endl;
        return 1;
    }

    /* Register the error strings for libssl functions */
    SSL_load_error_strings();

    /* Register the SSL/TLS ciphers and digests */
    SSL_library_init();

    /* Create a new SSL context object to establish TLS/SSL enabled connections */
    SSL_CTX *ssl_ctx = SSL_CTX_new(SSLv23_client_method());

    /* Attaching SSL connection to the socket */
    SSL *conn = SSL_new(ssl_ctx);
    SSL_set_fd(conn, sockfd);
    SSL_connect(conn);

    result = SSL_write(conn, mess, sizeof mess);
    if (result < 0)
    {
        std::cout << "Socket Client: error writing to the SSl socket" << std::endl;
        return 1;
    }

    result = SSL_read(conn, buff, sizeof buff);
    if (result < 0)
    {
        std::cout << "Socket Client: error reading from the SSL socket" << std::endl;
        return 1;
    }

    std::cout << "**START**" << std::endl;
    std::cout << buff << std::endl; 
    std::cout << "**END**" << std::endl; 

    SSL_free(conn);
    close(sockfd);
    SSL_CTX_free(ssl_ctx);

    return 0;
}
