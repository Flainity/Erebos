#pragma once

#include "pch.h"

#include "Fiesta/Structures.h"

namespace Fiesta::Classes::ZoneServer::Types
{
    typedef Structures::MY_SERVER* (__thiscall* t_zs_worlddata)(void* zoneServer);
}
