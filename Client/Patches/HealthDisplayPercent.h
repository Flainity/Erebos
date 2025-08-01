#pragma once

#include <string>
#include <vector>

#include "Fiesta/Templates.h"
#include "Fiesta/Pointers.h"

namespace Patches
{
    class HealthDisplayPercent
    {
    public:
        static void Install()
        {
            constexpr char percentStr[] = "%d%%";
            memcpy(reinterpret_cast<void*>(0x9DB530), percentStr, sizeof(percentStr));
            
            // 1. JMP Patch bei 0x59C3F1 → springt zu Code Cave
            constexpr BYTE patch[] = {
                0xE9, 0x1A, 0x0C, 0x3D, 0x00, // JMP 0x96D80A
                0x90, 0x90                    // NOPs zum Überschreiben der PUSH EAX + MOV ECX
            };
            Fiesta::Templates::PatchMemory(reinterpret_cast<void*>(0x59C3F1), patch, sizeof(patch));

            // 2. Code Cave bei 0x96D80A
            constexpr BYTE cave[] = {
                0xB9, 0x90, 0x70, 0xA9, 0x00,             // mov ecx, 0x00A97090 ; g_kUser
                0xE8, 0xFB, 0xA4, 0x06, 0x00,             // call 0x005C6810 ; MaxHP (rel to next instr)

                0x89, 0xC7,                               // mov edi, eax

                0xB9, 0x90, 0x70, 0xA9, 0x00,             // mov ecx, 0x00A97090 ; g_kUser
                0xE8, 0x00, 0xA5, 0x06, 0x00,             // call 0x005C6800 ; HP

                0x6B, 0xC0, 0x64,                         // imul eax, eax, 100
                0x31, 0xD2,                               // xor edx, edx
                0xF7, 0xFF,                               // div edi

                0x50,                                     // push eax
                0x68, 0x30, 0xB5, 0x9D, 0x00,             // push 0x00B3F000 ; "%d%%"
                0xE8, 0x7D, 0x53, 0x06, 0x00,             // call 0x005F9830 ; fs

                0xE9, 0xFB, 0xFF, 0x00, 0x00              // jmp 0x59C40C (relativ)
            };
            Fiesta::Templates::PatchMemory(reinterpret_cast<void*>(0x96D80A), cave, sizeof(cave));
        }
    };
}
