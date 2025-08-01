#pragma once

#include "pch.h"

namespace Fiesta::Classes::LuaScript::Pointers
{
    POINTER FunctionCall = 0x5D7BC0;

    POINTER SetGlobal = 0x5F8820;
    POINTER PushClosure = 0x5F82D0;
    POINTER PushNumber = 0x5F8110;
    POINTER PushBoolean = 0x5F8360;
    POINTER ToNumber = 0x5F7AD0;
    POINTER ToString = 0x5F7D80;
    POINTER ToBoolean = 0x5F7D00;
    POINTER PushNil = 0x5F80F0;
    POINTER PushString = 0x5F8210;
    POINTER SetTop = 0x5F7300;
    POINTER GetTop = 0x5F72E0;
    POINTER GetTable = 0x5F8430;
    POINTER CreateTable = 0x5F8650;
}