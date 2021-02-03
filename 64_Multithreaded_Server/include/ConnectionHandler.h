#ifndef CONNECTION_HANDLER_H_
#define CONNECTION_HANDLER_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string>

namespace socketServerClient {
    /* Class declaration, due to circular reference problem */
    class SocketServer;    
    class ConnectionHandler
    {
    public:
        ConnectionHandler(SocketServer *parent, sockaddr_in *client, int clientSockFd);
        int createThread();
        void waitThread();
        void stop() { running = false; }
        virtual int send(std::string message);
        virtual std::string receive(int size);
        virtual ~ConnectionHandler();
    protected:
        virtual void threadLoop();
    private:
        sockaddr_in *client; 
        int clientSockFd;
        pthread_t thread;
        bool running;
        SocketServer *parent;
        static void *threadH(void *handler)
        { 
            ((ConnectionHandler *)handler)->threadLoop();
            return NULL; 
        }
    };

}   /* namespace socketServerClient */

#endif /* CONNECTION_HANDLER_H_ */