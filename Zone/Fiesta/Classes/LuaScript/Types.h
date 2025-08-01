#pragma once

#include "pch.h"

namespace Fiesta::Classes::LuaScript::Types
{
    typedef bool(__thiscall* t_lua_FunctionCall)(void* self, const char* functionName, void* arguments);

    // Since there is no namespace for native lua function, we use this namespace
    typedef void(__cdecl* t_lua_setglobal)(lua_State* state, const char* var);
    typedef void(__cdecl* t_lua_pushcclosure)(lua_State* state, void* function, int n);
    typedef void(__cdecl* t_lua_pushnumber)(lua_State* state, long double n);
    typedef void(__cdecl* t_lua_pushboolean)(lua_State* state, int);
    typedef double(__cdecl* t_lua_tonumberx)(lua_State* state, int index, int* isNumber);
    typedef const char* (__cdecl* t_lua_tolstring)(lua_State* state, int index, unsigned int* length);
    typedef void(__cdecl* t_lua_pushnil)(lua_State* state);
    typedef int(__cdecl* t_lua_next)(lua_State* state, int index);
    typedef int(__cdecl* t_lua_gettop)(lua_State* state);
    typedef int(__cdecl* t_lua_type)(lua_State* state, int index);
    typedef const char* (__cdecl* t_lua_pushstring)(lua_State* state, const char* string);
    typedef void(__cdecl* t_lua_gettable)(lua_State* state, int index);
    typedef void(__cdecl* t_lua_settop)(lua_State* state, int index);
    typedef BOOL(__cdecl* t_lua_toboolean)(lua_State* state, int index);
    typedef void(__cdecl* t_lua_createtable)(lua_State* state, int narray, int nrecords);
}