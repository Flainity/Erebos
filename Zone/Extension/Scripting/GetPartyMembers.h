#pragma once

#include "pch.h"

namespace Extension::Scripting
{
    class GetPartyMembers
    {
    public:
        static const char* Command;
        static int Execute(lua_State* lua_script);
    };
}
