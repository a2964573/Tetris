#ifndef _ENVIRONMENT_H
#define _ENVIRONMENT_H

#include <iostream>
#include <string>

class Environment
{
    private:
        std::string _id;
        std::string _passwd;
        std::string _name;

    protected:

    public:
        Environment();
};

#endif // _ENVIRONMENT_H