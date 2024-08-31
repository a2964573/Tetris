#ifndef _CLIENT_H
#define _CLIENT_H

#include "../define.h"
#include "../common.h"

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
		int clientSocketConnect();
		int clientSocketSend();
		int clientSocketReceive();
		int clientSocketClose();
};

#endif // _CLIENT_H

