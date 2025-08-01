#pragma once

#include "pch.h"
#include <string>

namespace Extension::Scripting
{
    class GetChargeItem
    {
    public:
        static const char* Command;
        static int Execute(lua_State* lua_script);
    };
}
