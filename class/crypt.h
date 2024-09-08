#ifndef _CRIPT_H
#define _CRIPT_H

#include "../include/define.h"
#include "../include/common.h"

#include "util.h"

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

#define EXRPATH "../external/RSA"

int cryptEnRSA(const std::string& publicKey, const std::string& base, std::string& output);
int cryptDeRSA(const std::string& privateKey, const std::string& encrypt, std::string& output);
int cryprtGetFileKey(std::string type, std::string& output);                                                                  


#endif // _CRIPT_H

