#pragma once

#include <string>
#include <vector>

#include "Fiesta/Templates.h"
#include "Fiesta/Pointers.h"

namespace Patches
{
    class RoarItemID
    {
    public:
        static void Install()
        {
            constexpr BYTE newAddressData[] = { 0x66, 0x67, 0x68, 0x4e, 0x10 };
            const auto newAddressPtr01 = reinterpret_cast<void*>(0x57fed5);
            const auto newAddressPtr02 = reinterpret_cast<void*>(0x57ff02);

            Fiesta::Templates::PatchMemory(newAddressPtr01, newAddressData, 5);
            Fiesta::Templates::PatchMemory(newAddressPtr02, newAddressData, 5);
        }
    };
}
