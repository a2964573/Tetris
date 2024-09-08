#include "login.h"


int login_proceduer(User& user)
{
	Client client;

	std::string menu;

	utilPrintDescription(LOGIN_MENU);
	utilInputString(1, menu);

	int rtn;
	switch(loginGetMenuDivision(menu)) {
		case MENU_LOGIN :
			rtn = userLogin(user, client);
		break;
		case MENU_SIGNUP:
			rtn = userSignup(user, client);
		break;
		case MENU_FIND  :
		// break;
		case MENU_CHANGE:
		// break;
		default:
			UTILLOG(LOGLV_ERR, "Login Proceduer User Select Mode[%s]", menu.c_str());
			rtn = 0;
		break;
	}


    return rtn;
}

int loginGetMenuDivision(std::string menu)
{
	std::transform(menu.begin(), menu.end(), menu.begin(), ::tolower);

	if(menu.compare("login") == 0) {
		return MENU_LOGIN;
	}
	else
	if(menu.compare("signup") == 0) {
		return MENU_SIGNUP;
	}
	else
	if(menu.compare("find") == 0) {
		return MENU_FIND;
	}
	else
	if(menu.compare("change") == 0) {
		return MENU_CHANGE;
	}
	else {
		return 0;
	}
}

int userSignup(User& user, Client& client)
{

	return 0;
}

int userLogin(User& user, Client& client)
{
	std::string id;
	std::string pw;

	utilPrintDescription("아이디 입력");
	utilInputString(0, id);

	utilPrintDescription("비밀번호 입력");
	utilInputStringHidden(pw);

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

	int rtn = requestLogin(client);
	if(rtn < 0) {
        UTILLOG(LOGLV_ERR, "Request Login failed.");
        return -1;
	}

	return 0;
}

int requestLogin(Client& client)
{
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
	if(rtn < 0) {
		UTILLOG(LOGLV_ERR, "Recv failed.");
		return -1;
	}
	int rlen = rtn;

	UTILLOG(LOGLV_DBG, "Receive Data[%d:%s]", rlen, recvData.data());
	
	rtn = client.clientSocketClose();
	if(rtn < 0) {
        UTILLOG(LOGLV_ERR, "Close failed.");
        return -1;
    }

	return rlen;
}

