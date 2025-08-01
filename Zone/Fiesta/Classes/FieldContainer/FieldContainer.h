#pragma once

#include "pch.h"

#include "Pointers.h"
#include "Types.h"

namespace Fiesta::Classes::FieldContainer
{
    class FieldContainer
    {
    public:
        SIGNATURE Original_CanEnterDungeon = reinterpret_cast<Types::t_fc_CanEnterIndun>(Pointers::CanEnterIndun);
        SIGNATURE Original_GetInstanceDungeonInfoByMapName = reinterpret_cast<Types::t_fc_GetInstanceDungeonInfoByMapName>(Pointers::GetInstanceDungeonInfoByMapName);
        SIGNATURE Original_FindMap = reinterpret_cast<Types::t_fc_FindMap>(Pointers::FindMap);
    };
}