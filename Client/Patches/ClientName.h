#pragma once

#include <string>
#include <vector>

#include "Fiesta/Templates.h"
#include "Fiesta/Pointers.h"

namespace Patches
{
    class ClientName
    {
    public:
        static void Install()
        {
            const std::string newName = "Vision of the past - v1.000.000";
            const char* newNamePatchData = newName.c_str();
            const std::vector<BYTE> stringData(newNamePatchData, newNamePatchData + newName.length() + 1);

            constexpr BYTE newAddressData[] = { 0x68, 0x22, 0xCB, 0x96 };
            const auto newAddressPtr = reinterpret_cast<void*>(0x96CB22);

            if (Fiesta::Templates::PatchMemory(newAddressPtr, stringData.data(), stringData.size()))
            {
                const auto clientNamePtr = reinterpret_cast<char*>(Fiesta::Pointers::Globals::ClientName);
                Fiesta::Templates::PatchMemory(clientNamePtr, newAddressData, sizeof newAddressData);
            }
        }
    };
}
