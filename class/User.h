#ifndef _USER_H
#define _USER_H

#include "../define.h"
#include "../common.h"

class User
{
    private:
        std::string _id;
        std::string _name;
        int _os_type;

    protected:

    public:
        User();
        ~User();

        std::string userGetId();
        std::string userGetName();
        int userGetOSType();

        int userSetId(const std::string& id);
        int userSetName(const std::string& name);
        int userSetOSType();
};

#endif // _USER_H