#pragma once

#include "pch.h"

namespace Fiesta::Classes::GameFrameWork::Types
{
    typedef void* (__thiscall* t_SendNetMsgWorldMgr)(void* self, unsigned short department, unsigned short command, void* pProto, int dataLength);
    typedef void* (__thiscall* t_AddNetMsgToWorldMgr)(void* self, unsigned short department, unsigned short command);
}