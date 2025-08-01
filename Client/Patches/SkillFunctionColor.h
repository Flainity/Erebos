#pragma once

#include <string>
#include <vector>

#include "Fiesta/Templates.h"
#include "Fiesta/Pointers.h"

namespace Patches
{
    class SkillFunctionColor
    {
    public:
        static void Install()
        {
            constexpr BYTE newColorData[] = { 0x68, 0xF0, 0x95, 0xA6, 0x00 };
            const auto address = reinterpret_cast<void*>(0x58EA14);

            Fiesta::Templates::PatchMemory(address, newColorData, sizeof(newColorData));
        }
    };
}
