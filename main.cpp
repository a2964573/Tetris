#include "main.h"

int main()
{
    User user;
    Util util;

    user.userSetOSType();
    std::cout << "Welcome to the Tetris!! OS by " << user.userGetOSType() << "." << std::endl;

    std::string id;
    util.utilPrintDescription("Id ют╥б");
    util.utilInputString(id);

    return 0;
}