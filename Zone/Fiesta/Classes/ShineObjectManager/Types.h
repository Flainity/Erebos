#pragma once

#include "pch.h"

#include "Fiesta/Structures.h"

namespace Fiesta::Classes::ShineObjectManager::Types
{
    typedef Structures::ShineObjectClass::ShineObject* (__thiscall* t_som_GetObject)(void* self, unsigned short handle);
    typedef void* (__thiscall* t_som_FindPlayer)(void* self, unsigned int charregnum);
    typedef void* (__thiscall* t_som_FindPlayerName)(void* self, Structures::Name5* charName);
}
