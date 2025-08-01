#pragma once

#include <string>
#include <vector>

#include "Fiesta/Templates.h"
#include "Fiesta/Pointers.h"

namespace Patches
{
    class LevelDisplay
    {
    public:
        static void Install()
        {
            constexpr BYTE targetWindowLevelData[] = { 0x83, 0xE8, 0x10 };
            const auto targetWindowLevel = reinterpret_cast<void*>(0x5A5C37);

            Fiesta::Templates::PatchMemory(targetWindowLevel, targetWindowLevelData, sizeof(targetWindowLevelData));

            constexpr BYTE newData2[] = { 0x31, 0xD2, 0x90 };
            const auto address2 = reinterpret_cast<void*>(0x566DE7);

            Fiesta::Templates::PatchMemory(address2, newData2, sizeof(newData2));

            constexpr BYTE newData3[] = { 0xE9, 0xA8, 0x00, 0x00, 0x00, 0x90 };
            const auto address3 = reinterpret_cast<void*>(0x52822C);

            Fiesta::Templates::PatchMemory(address3, newData3, sizeof(newData3));
        }
    };
}
