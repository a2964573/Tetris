#include "login.h"

int login_proceduer(User& user)
{
///////////////////////////////////////////////////////////////////////////////
// input
	std::string id;
	std::string pw;

	utilPrintDescription("아이디 입력");
	utilInputString(id);

	utilPrintDescription("비밀번호 입력");
	utilInputString(pw);

///////////////////////////////////////////////////////////////////////////////
// Client
	Client client;

	LGIN0001_IB inbound;
	std::memset(&inbound, 0x20, sizeof(inbound));

	std::memcpy(&inbound.user_id, id.data(), id.size());
	std::memcpy(&inbound.user_pw, pw.data(), pw.size());

	HEADER header;
	memset(&header, 0x20, sizeof(header));

	client.clientSetPacketHeader(SERVICE_LGIN001, "", header);

	char buffer[1024] = {0,};
	int  blen = sprintf(&buffer[0   ], "%s", header.length  );
	     blen = sprintf(&buffer[blen], "%s", inbound.user_id);

	client.clientSetSendBuffer(blen, buffer);

	UTILLOG(LOGLV_DBG, "send[%d:%.*s]", blen, blen, buffer);

///////////////////////////////////////////////////////////////////////////////

	int rtn = 0;

	rtn = client.clientSetServerIp("SERVER_IP");
	if(rtn < 0) {
		UTILLOG(LOGLV_ERR, "Server IP setting failed.");
		return -1;
	}

	UTILLOG(LOGLV_DBG, "Server IP[%s]", client.clientGetServerIp().c_str());

	rtn = client.clientSetServerPort("SERVER_PORT");
	if(rtn < 0) {
		UTILLOG(LOGLV_ERR, "Server port setting failed.");
		return -1;
	}

	UTILLOG(LOGLV_DBG, "Server port[%d]", client.clientGetServerPort());

	rtn = client.clientSocketCreate();
	if(rtn < 0) {
		UTILLOG(LOGLV_ERR, "Create client socket failed.");
		return -1;
	}

	UTILLOG(LOGLV_DBG, "Server Socket File Descirptor[%d]", client.clientGetSocketFileDescriptor());

	rtn = client.clientSocketConnect();
	if(rtn < 0) {
		UTILLOG(LOGLV_ERR, "Conncet socket failed.");
		return -1;
	}
	UTILLOG(LOGLV_DBG, "Connect Server Success!");

	rtn = client.clientSocketSend();
	if(rtn < 0) {
		UTILLOG(LOGLV_ERR, "Send failed.");
		return -1;
	}
	UTILLOG(LOGLV_DBG, "Send Data Success!");

	std::string recvData;
	rtn = client.clientSocketReceive(recvData);

	UTILLOG(LOGLV_DBG, "Receive Data[%d:%s]", recvData.length(), recvData.c_str());
	
	client.clientSocketClose();

    return 0;
}

