#include "main.h"

int main()
{
    User user;
    Util util;

    user.userSetOSType();

	util.utilClearScreen(user.userGetOSType());

    std::cout << "Welcome to the Tetris!! OS by " << user.userGetOSType() << "." << std::endl;

    std::string id;
    std::string pw;
	while(true) {
		util.utilPrintDescription("Id 입력");
		if(util.utilInputString(id) <= 0) {
			std::cout << "ID를 입력하세요" << std::endl;
			continue;
		}
		user.userSetId(id);

		util.utilPrintDescription("PW 입력");
		if(util.utilInputString(pw) <= 0) {
			std::cout << "PW를 입력하세요" << std::endl;
			continue;
		}

		std::cout << "ID: " << user.userGetId() << " / PW: " << pw << "." << std::endl;
		break;
	}

    return 0;
}
