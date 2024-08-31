#include "User.h"

User::User()
{
	_login_state = false;
    _id          = "";
    _name        = "";
    _os_type     = User::userSetOSType();
}

User::~User()
{
	_login_state = false;
    _id          = "";
    _name        = "";
    _os_type     = 0;
}

bool User::userGetLoginState()
{
    return _login_state;
}

int User::userSetLoginState(bool state)
{
    _login_state = state;

    return 0;
}

std::string User::userGetId()
{
    return _id;
}

int User::userSetId(const std::string& id)
{
    _id = id;

    return 0;
}

std::string User::userGetName()
{
    return _name;
}

int User::userSetName(const std::string& name)
{
    _name = name;

    return 0;
}

int User::userGetOSType()
{
    return _os_type;
}

int User::userSetOSType()
{
    #if defined(_WIN32) || defined(_WIN64)
        _os_type = OS_WINDOWS;
    #elif defined(__linux__)
        _os_type = OS_LINUX;
    #elif defined(__APPLE__) || defined(__MACH__)
        _os_type = OS_MACOS;
    #endif

    return _os_type;
}

