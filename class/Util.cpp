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

int Util::utilPrintDescription(const std::string desc)
{
    std::string description = "echo " + desc;
    system(description.c_str());

    return 0;
}

int Util::utilInputString(std::string output)
{
    std::getline(std::cin, output);
    return output.length();
}