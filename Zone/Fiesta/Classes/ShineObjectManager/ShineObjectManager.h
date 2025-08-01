#pragma once

#include "pch.h"

#include "Types.h"
#include "Pointers.h"

namespace Fiesta::Classes::ShineObjectManager
{
    class ShineObjectManager
    {
    public:
        SIGNATURE Original_GetObject = reinterpret_cast<Types::t_som_GetObject>(Pointers::GetShineObject);
        SIGNATURE Original_FindPlayer = reinterpret_cast<Types::t_som_FindPlayer>(Pointers::FindPlayer);
        SIGNATURE Original_FindPlayerByName = reinterpret_cast<Types::t_som_FindPlayerName>(Pointers::FindPlayerName);
    };
}
