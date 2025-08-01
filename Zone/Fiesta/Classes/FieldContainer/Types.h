#pragma once

#include "pch.h"

#include "Fiesta/Structures.h"

namespace Fiesta::Classes::FieldContainer::Types
{
    typedef Enums::ENTER_MAP_ERR(__stdcall* t_fc_CanEnterIndun)(Structures::ShineObjectClass::ShineObject* player, Structures::InstanceDungeonInfo* dungeonInfo, unsigned int* registerNumber, Enums::INSTANCE_DUNGEON::CATEGORY* category);
    typedef Structures::InstanceDungeonInfo* (__thiscall* t_fc_GetInstanceDungeonInfoByMapName)(void* fieldContainer, Structures::MapNameStruct* mapName, Enums::ID_LEVEL_TYPE levelType);
    typedef Structures::FieldMap* (__thiscall* t_fc_FindMap)(void* fieldContainer, const char* mapName);
}
