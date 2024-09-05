#ifndef _CLIENT_H
#define _CLIENT_H

#include "../include/define.h"
#include "../include/common.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class Client
{
    private:

    protected:

    public:
        Client();
        ~Client();
		int clientSocketCreate();
		int clientSocketConnect(int sockfd, std::string ip, std::string port);
		int clientSocketSend(int sockfd, std::string sendData);
		int clientSocketReceive(int sockfd, std::string& output);
		int clientSocketClose(int sockfd);
};

#endif // _CLIENT_H

