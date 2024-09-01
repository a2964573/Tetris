#include "client.h"

Client::Client()
{

}

Client::~Client()
{

}

int Client::clientSocketCreate()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) {
		std::cout << "Socket creation error" << std::endl;
		return -1;
	}

	return sockfd;
}

int Client::clientSocketConnect(int sockfd, std::string ip, std::string port)
{
	int rtn = 0;
	struct sockaddr_in server_addr = {0,};

	server_addr.sin_family = AF_INET;
	server_addr.sin_port   = htons(std::stoi(port));

	rtn = inet_pton(AF_INET, ip.c_str(), 0);
	if(rtn < 0) {
		std::cerr << "Error: 지정된 주소체계 반환 실패"  << std::endl;
		return -1;
	}
	else
	if(rtn == 0) {
		std::cerr << "Error: 잘못된 형식의 주소"  << std::endl;
		return 0;
	}

	if(connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		std::cerr << "Error: 연결 실패"  << std::endl;
		return -1;
	}

	return rtn;
}

int Client::clientSocketSend(int sockfd, std::string sendData)
{
	std::cout << "client send data [" << sendData << "]" << std::endl;

	return send(sockfd, sendData.c_str(), sendData.length(), 0);
}

int Client::clientSocketReceive(int sockfd, std::string& output)
{
	char buffer[1024] = {0,};
	read(sockfd, &buffer[0], sizeof(buffer));

	output = &buffer[0];

	std::cout << "client recv data [" << output << "]" << std::endl;

	return output.length();
}

int Client::clientSocketClose(int sockfd)
{
	return close(sockfd);
}

