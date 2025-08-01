#pragma once

#include <string>
#include <vector>

#include "Fiesta/Templates.h"
#include "Fiesta/Pointers.h"
#include "Utility/Logging/FileLogger.h"

namespace Patches
{
    class StatDisplay
    {
    public:
        static void Install()
        {
            Utility::Logging::FileLogger logger;
            auto newFormat = "+%d %s";
            Fiesta::Templates::PatchMemory(reinterpret_cast<void*>(0x990460), newFormat, 1 + strlen(newFormat));

            auto codeCave = static_cast<BYTE*>(VirtualAlloc(nullptr, 0x100, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));

            if (!codeCave)
                logger.Debug("CodeCave could not be set, returning");

            uintptr_t fsAddress = 0x7391B0;
            uintptr_t returnAddress = 0x5292C5;

            intptr_t callToFsOffset = (intptr_t)fsAddress - ((intptr_t)(codeCave + 9 + 5));
            intptr_t jumpBackOffset = (intptr_t)returnAddress - ((intptr_t)(codeCave + 9 + 14));

            std::vector<BYTE> caveCode = {
                0x57,                               // push edi
                0x50,                               // push eax
                0x68, 0x60, 0x04, 0x99, 0x00,       // push 0x990460
                0xB8, 0, 0, 0, 0,                   // mov eax, fsAddress
                0xFF, 0xD0,                         // call eax
                0xE9, 0, 0, 0, 0                    // jmp zurück
            };

            *reinterpret_cast<uint32_t*>(&caveCode[9]) = fsAddress;
            *reinterpret_cast<int32_t*>(&caveCode[14]) = (int32_t)jumpBackOffset;

            Fiesta::Templates::PatchMemory(codeCave, caveCode.data(), caveCode.size());

            uintptr_t originalAddress = 0x005292BA;
            uintptr_t jumpToCaveOffset = reinterpret_cast<uintptr_t>(codeCave) - (originalAddress + 5);

            BYTE patchJump[5] = {
                0xE9,
                0, 0, 0, 0
            };
            *reinterpret_cast<int32_t*>(&patchJump[1]) = static_cast<int32_t>(jumpToCaveOffset);

            Fiesta::Templates::PatchMemory(reinterpret_cast<void*>(originalAddress), patchJump, sizeof(patchJump));
        }
    };
}
