#ifndef _CLIENT_H
#define _CLIENT_H

#include "../include/define.h"
#include "../include/common.h"
#include "../include/packet.h"

#include "../class/util.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PACKET_MAX_LEN 1024

class Client
{
    private:
		std::string _server_ip;
		int _server_port;
		int _sockfd;
		int _send_len;
		char _send_buffer[PACKET_MAX_LEN];
		char _recv_buffer[PACKET_MAX_LEN];
		struct sockaddr_in _address;

    protected:

    public:
        Client();
        ~Client();
		std::string clientGetServerIp();
		int clientSetServerIp(std::string name);
		int clientGetServerPort();
		int clientSetServerPort(std::string name);
		int clientGetSocketFileDescriptor();
		int clientGetReceiveBuffer(char* output, int len);
		int clientSetPacketHeader(std::string name, std::string message, HEADER& output);
		int clientGetSendBuffer(char* output, int len);
		int clientSetSendBuffer(int len, char* buffer);
		int clientSocketCreate();
		int clientSocketConnect();
		int clientSocketSend();
		int clientSocketReceive(std::string& output);
		int clientSocketClose();
};

#endif // _CLIENT_H

