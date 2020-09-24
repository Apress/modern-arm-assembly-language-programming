//-------------------------------------------------
//               Misc.h
//-------------------------------------------------

#pragma once
#include <iostream>
#include <string>

class Misc
{
public:
    static bool IsExt(const std::string& fn, const std::string& fn_ext_test)
    {
        std::string fn_ext = fn.substr(fn.find_last_of(".") + 1);

        return fn_ext.compare(fn_ext_test) == 0;
    }
};

