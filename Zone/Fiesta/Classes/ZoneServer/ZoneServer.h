#pragma once

#include "pch.h"

#include "Pointers.h"
#include "Types.h"

namespace Fiesta::Classes::ZoneServer
{
    class ZoneServer
    {
    public:
        SIGNATURE Original_WorldData = reinterpret_cast<Types::t_zs_worlddata>(Pointers::WorldData);
    };
}