#pragma once

#include "pch.h"

#include "Types.h"
#include "Pointers.h"
#include "Fiesta/Structures.h"

namespace Fiesta::Classes::LuaScript
{
    class LuaScript
    {
    public:
        SIGNATURE Original_FunctionCall = reinterpret_cast<Types::t_lua_FunctionCall>(Pointers::FunctionCall);
        SIGNATURE Original_SetGlobal = reinterpret_cast<Types::t_lua_setglobal>(Pointers::SetGlobal);

        SIGNATURE Original_ToNumber = reinterpret_cast<Types::t_lua_tonumberx>(Pointers::ToNumber);
        SIGNATURE Original_ToString = reinterpret_cast<Types::t_lua_tolstring>(Pointers::ToString);
        SIGNATURE Original_ToBoolean = reinterpret_cast<Types::t_lua_toboolean>(Pointers::ToBoolean);
        
        SIGNATURE Original_PushClosure = reinterpret_cast<Types::t_lua_pushcclosure>(Pointers::PushClosure);
        SIGNATURE Original_PushNumber = reinterpret_cast<Types::t_lua_pushnumber>(Pointers::PushNumber);
        SIGNATURE Original_PushString = reinterpret_cast<Types::t_lua_pushstring>(Pointers::PushString);
        SIGNATURE Original_PushBoolean = reinterpret_cast<Types::t_lua_pushboolean>(Pointers::PushBoolean);
        SIGNATURE Original_PushNil = reinterpret_cast<Types::t_lua_pushnil>(Pointers::PushNil);

        static Structures::ShineObjectClass::ShinePlayer* GetPlayer(lua_State* lua_script);

    private:
        bool FunctionCall(const char* functionName, void* arguments);
    };
}
