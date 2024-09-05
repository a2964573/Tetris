#ifndef _UTIL_H
#define _UTIL_H

#include "../include/define.h"
#include "../include/common.h"


int utilClearScreen(int os_type);
int utilPrintDescription(const std::string desc);
int utilInputString(std::string& output);
int utilInputChar(char& output);
int utilInputNumber(int output);


#endif // _UTIL_H

