#ifndef _UTIL_H
#define _UTIL_H

#include "../include/define.h"
#include "../include/common.h"

#define UTILLOG(level, format, ...) utilLogging(__FILE__, __FUNCTION__, __LINE__, level, format, ##__VA_ARGS__)

int utilLogging(const char* fileName, const char* funcName, const int line, int level, const char* format, ...);
int utilGetEnvValue(std::string file, std::string key, std::string& output);
int utilGetNowDate(std::string* output);
int utilGetNowTime(std::string* output);
int utilClearScreen(int os_type);
int utilPrintDescription(const std::string desc);
int utilInputString(std::string& output);
int utilInputChar(char& output);
int utilInputNumber(int output);
int utilItos(int num, std::string& output);


#endif // _UTIL_H

