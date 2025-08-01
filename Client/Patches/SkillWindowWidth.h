#pragma once

#include <string>
#include <vector>

#include "Fiesta/Templates.h"
#include "Fiesta/Pointers.h"

namespace Patches
{
    class SkillWindowWidth
    {
    public:
        static void Install()
        {
            constexpr BYTE newAddressData[] = { 0xC7, 0x85, 0xCC, 0xFE, 0xFF, 0xFF, 0x6C, 0x01, 0x00, 0x00 };
            const auto address = reinterpret_cast<void*>(0x58c0d9);

            Fiesta::Templates::PatchMemory(address, newAddressData, sizeof(newAddressData));
        }
    };
}
