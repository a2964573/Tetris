#ifndef _USER_H
#define _USER_H

#include "../include/define.h"
#include "../include/common.h"

class User
{
    private:
		bool _login_state;
        std::string _id;
        std::string _name;
        int _os_type;

    protected:

    public:
        User();
        ~User();

		bool userGetLoginState();
        std::string userGetId();
        std::string userGetName();
        int userGetOSType();

		int userSetLoginState(bool state);
        int userSetId(const std::string& id);
        int userSetName(const std::string& name);
        int userSetOSType();
};

#endif // _USER_H

