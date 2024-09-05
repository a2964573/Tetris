#ifndef _ENVIRONMENT_H
#define _ENVIRONMENT_H

#include "../include/define.h"
#include "../include/common.h"

class Environment
{
    private:
		std::string _env_file;
		std::string _env_fileName;
		std::string _env_path;

    protected:

    public:
        Environment();
        ~Environment();
		int envGetValue(const std::string key, std::string& output);
};

#endif // _ENVIRONMENT_H

