#include "client.h"

Client::Client()
{

}

Client::~Client()
{

}

int Client::clientSocketCreate()
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0) {
		std::cout << "Socket creation error" << std::endl;
		return -1;
	}

	return sock;
}

int Client::clientSocketConnect()
{
	return 0;
}

int Client::clientSocketSend()
{
	return 0;
}

int Client::clientSocketReceive()
{
	return 0;
}

int Client::clientSocketClose()
{
	return 0;
}

