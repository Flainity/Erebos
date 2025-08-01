#pragma once

#include "pch.h"

namespace Fiesta::Classes::FieldContainer::Pointers
{
    CAST_POINTER FieldContainer = reinterpret_cast<void*>(0xCFD2B70);
    
    POINTER GetInstanceDungeonInfoByMapName = 0x4844E0;
    POINTER CanEnterIndun = 0x4624D0;
    POINTER FindMap = 0x466A60;
}