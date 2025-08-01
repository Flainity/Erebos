#pragma once

#include "pch.h"

namespace Fiesta::Classes::PgNet::Types
{
    typedef void* (__thiscall* t_SendNetMsg)(void* self, void* pdata, int length);
}