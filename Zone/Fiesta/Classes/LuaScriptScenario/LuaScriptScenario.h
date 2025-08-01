#pragma once

#include "pch.h"

#include "Types.h"
#include "Pointers.h"
#include "Fiesta/Structures.h"
#include "Fiesta/Templates.h"

#include "Utility/HookRegistry.h"

namespace Fiesta::Classes::LuaScriptScenario
{
    class LuaScriptScenario
    {
    public:
        SIGNATURE Original_FuncSet = reinterpret_cast<Types::t_lua_FuncSet>(Pointers::FuncSet);

    private:
        static void AddCommand(const Structures::LuaScript* script, const char* command, void* function);
        char FuncSet();

        REGISTER_HOOK("LuaScriptScenario::FuncSet", "LuaCommands", Original_FuncSet, FuncSet)
    };
}
