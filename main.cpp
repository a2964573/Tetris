#include "main.h"

int main()
{
	if(main_initialization() < 0) {
		return -1;
	}

	main_proceduer();

    return 0;
}

int main_initialization()
{
	return 0;
}

int main_proceduer()
{
	User user;
	Util util;

	char mode;
	int  rtn = 0;

	while(true) {
		util.utilClearScreen(user.userGetOSType());

		if(user.userGetLoginState()) {
			// rtn = loginProceduer(user);
			if(rtn < 0) {
				break;
			}
			continue;
		} else {
			util.utilPrintDescription("모드를 입력하시오.");
			util.utilInputChar(mode);
			std::cout << "입력된 모드 [" <<  mode << "]" << std::endl;
			/*
			if(mode = MODE_SETTING) {
				rtn = settingProceduer(user);
			}
			else
			if(mode = MODE_CHAT) {
				rtn = chatProceduer(user);
			}
			else
			if(mode = MODE_GAME) {
				rtn = gameProceduer(user);
			}
			*/
			break;

			if(rtn < 0) {
				break;
			}
			continue;
		}
	}

	return 0;
}

