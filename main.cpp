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
		util.utilPrintDescription("Id �Է�");
		if(util.utilInputString(id) <= 0) {
			std::cout << "ID�� �Է��ϼ���" << std::endl;
			continue;
		}
		user.userSetId(id);

		util.utilPrintDescription("PW �Է�");
		if(util.utilInputString(pw) <= 0) {
			std::cout << "PW�� �Է��ϼ���" << std::endl;
			continue;
		}

		std::cout << "ID: " << user.userGetId() << " / PW: " << pw << "." << std::endl;
		break;
	}

    return 0;
}
