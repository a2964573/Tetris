#ifndef _UTIL_H
#define _UTIL_H

#include "../define.h"
#include "../common.h"

class Util
{
    private:

    protected:

    public:
        Util();
        ~Util();

        int utilClearScreen(int os_type);
        int utilPrintDescription(const std::string desc);
        int utilInputString(std::string& output);
};


#endif // _UTIL_H

