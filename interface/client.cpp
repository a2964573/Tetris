#include "client.h"

Client::Client()
{
	_server_ip   = "";
	_server_port = 0;
	_sockfd      = 0;
	_send_len    = 0;
	_address     = {0,};
	_send_buffer[PACKET_MAX_LEN] = {0,};
	_recv_buffer[PACKET_MAX_LEN] = {0,};
}

Client::~Client()
{
	_server_ip   = "";
	_server_port = 0;
	_sockfd      = 0;
	_send_len    = 0;
	_address     = {0,};
	_send_buffer[PACKET_MAX_LEN] = {0,};
	_recv_buffer[PACKET_MAX_LEN] = {0,};
}

std::string Client::clientGetServerIp()
{
	return _server_ip;
}

int Client::clientSetServerIp(std::string name)
{
	std::string ip_s;
    std::string file = INTERFACE_ENV_PATH + std::string("/_interface.env");
    if(utilGetEnvValue(file, name, ip_s) < 0) {
        UTILLOG(LOGLV_ERR, "[%s] value get failed.", name);
        return -1;
    }
	_server_ip = ip_s;

    return 0;
}

int Client::clientGetServerPort()
{
	return _server_port;
}

int Client::clientSetServerPort(std::string name)
{
    std::string port_s;
    std::string file = INTERFACE_ENV_PATH + std::string("/_interface.env");
    if(utilGetEnvValue(file, name, port_s) < 0) {
        UTILLOG(LOGLV_ERR, "[%s] value get failed.", name);
        return -1;
    }
	_server_port = std::stoi(port_s);

    return _server_port;
}

int Client::clientGetSocketFileDescriptor()
{
	return _sockfd;
}

int Client::clientGetReceiveBuffer(char* output, int len)
{
    std::memcpy(output, &_recv_buffer, len);

    return 0;
}

int Client::clientSetPacketHeader(std::string name, std::string message, HEADER& output)
{
	if(name.size() > 0) {
		std::memcpy(&output.service_name, name.data(), sizeof(output.service_name));
	} else {
		std::memset(&output.service_name, 0x20       , sizeof(output.service_name));
	}

	if(message.size() > 0) {
		std::memcpy(&output.message, message.data(), sizeof(output.message));
	} else {
		std::memset(&output.message, 0x20          , sizeof(output.message));
	}

	return 0;
}

int Client::clientGetSendBuffer(char* output, int len)
{
	std::memcpy(output, &_send_buffer, len);

	return 0;
}

int Client::clientSetSendBuffer(int len, char* buffer)
{
	std::string len_s;
	int slen = utilItos(len, len_s);

	std::memcpy(&buffer[0], len_s.data(), slen);

	_send_len = sprintf(&_send_buffer[0], "%.*s", len, buffer);
	return _send_len;
}

int Client::clientSocketCreate()
{
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(_sockfd < 0) {
		UTILLOG(LOGLV_ERR, "Socket creation error");
		return -1;
	}

	return _sockfd;
}

int Client::clientSocketConnect()
{
	int rtn = 0;

	_address.sin_family = AF_INET;
	_address.sin_port   = htons(_server_port);

	rtn = inet_pton(AF_INET, _server_ip.c_str(), &_address.sin_addr);
	if(rtn < 0) {
		UTILLOG(LOGLV_ERR, "Error: 지정된 주소체계 반환 실패");
		return -1;
	}
	else
	if(rtn == 0) {
		UTILLOG(LOGLV_ERR, "Error: 잘못된 형식의 주소");
		return 0;
	}

	if(connect(_sockfd, (struct sockaddr*)&_address, sizeof(_address)) < 0) {
		UTILLOG(LOGLV_ERR, "Error: 연결 실패[%s]", strerror(errno));
		return -1;
	}

	return rtn;
}

int Client::clientSocketSend()
{
	UTILLOG(LOGLV_NOR, "client send data [%d:%.*s]", _send_len, _send_len, _send_buffer);

	return send(_sockfd, _send_buffer, _send_len, 0);
}

int Client::clientSocketReceive(std::string& output)
{
	char buffer[1024] = {0,};
	read(_sockfd, &buffer[0], sizeof(buffer));

	output = &buffer[0];

	UTILLOG(LOGLV_NOR, "client recv data[%d:%s]", output.size(), output.data());

	return output.size();
}

int Client::clientSocketClose()
{
	return close(_sockfd);
}

