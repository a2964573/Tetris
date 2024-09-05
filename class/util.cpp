#include "util.h"

int utilClearScreen(int os_type)
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

int utilPrintDescription(const std::string desc)
{
    std::string description = "echo " + desc;
    system(description.c_str());

    return 0;
}

int utilInputString(std::string& output)
{
    std::getline(std::cin, output);
    return output.length();
}

int utilInputChar(char& output)
{
	std::string input;
	std::getline(std::cin, input);
	output = input[0];

	return static_cast<int>(output);
}

int utilInputNumber(int output)
{
	std::string input;
	std::getline(std::cin, input);
    try {
        int rtn = std::stoi(input.substr(0, input.find(' ')));
        output = static_cast<int>(rtn);
		if(output < 0) {
			output = 0;
		}
    } catch(const std::invalid_argument& e) {
        std::cerr << "0 이상의 수를 입력해주세요." << std::endl;
		return -1;
    }
    
    return output;
}

