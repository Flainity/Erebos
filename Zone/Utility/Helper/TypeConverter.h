#pragma once

#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>

namespace Utility::Helper::TypeConverter
{
    inline bool StringToBoolean(std::string str)
    {
        std::ranges::transform(str, str.begin(), ::tolower);
        std::istringstream is(str);
        bool b;
        is >> std::boolalpha >> b;
        return b;
    }

    inline int StringToInt(std::string str)
    {
        return std::stoi(str);
    }
}