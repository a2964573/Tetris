#include "main.h"

int main()
{
	if(main_init() < 0) {
		return -1;
	}

	main_proceduer();

    return 0;
}

int main_init()
{
	return 0;
}

int main_proceduer()
{
	User user;

	char mode;
	int  rtn = 0;

	while(true) {
		utilClearScreen(user.userGetOSType());

		if(user.userGetLoginState()) {
			rtn = login_proceduer(user);
			if(rtn < 0) {
				break;
			}
			continue;
		} else {
			utilPrintDescription("모드를 입력하시오.");
			utilInputChar(mode);
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

