#pragma once

#include "pch.h"

#include "Fiesta/Structures.h"

namespace Fiesta::Classes::ItemDataBox::Types
{
    typedef Structures::ItemDataBoxIndex* (__thiscall* t_ArrayOperator)(void* itemDataBox, unsigned short itemID);
    typedef unsigned int(__thiscall* t_ToItemId)(void*, const char* ItemIndex);
}
