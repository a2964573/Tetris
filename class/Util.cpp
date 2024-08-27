#include "Util.h"

Util::Util()
{

}

Util::~Util()
{

}

int Util::utilClearScreen(int os_type)
{
    switch(os_type) {
        case OS_WINDOWS:
            return std::system("cls");
        break;
        case OS_LINUX:
            return std::system("clear");
        break;
        case OS_MAC:
        default:
            return -1;
    }

    return 0;
}