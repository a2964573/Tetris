#ifndef _CRIPT_H
#define _CRIPT_H

#include "../include/define.h"
#include "../include/common.h"

#include "util.h"

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

#define EXRPATH "/home/tester/Projects/Cpp/Tetris/external/RSA"

int cryptEnRSA(const std::string type, const std::string& base, std::string& output);
int cryptDeRSA(const std::string type, const std::string& encrypt, std::string& output);
int cryptInit(std::string type, BIO** keybio);
int cryprtGetFileKey(std::string type, std::string& output);                                                                  
int cryptEncodeBase64(const std::vector<uchar>& input, std::string& output);
int cryptDecodeBase64(const std::string& input, std::string& output);


#endif // _CRIPT_H

