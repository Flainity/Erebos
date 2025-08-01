#pragma once

#include <fstream>

#define MemberFunc(x) Fiesta::Templates::MemberFuncToPtr(&x)

namespace Fiesta::Templates
{
    inline __declspec(naked) void* MemberFuncToPtr(...)
    {
        __asm
        {
            mov eax, [esp + 4];
            retn;
        }
    }

    inline bool PatchMemory(void* address, const void* data, const int length)
    {
        DWORD protectRW = PAGE_EXECUTE_READWRITE;
        DWORD protectOLD;

        if (!VirtualProtect(address, length, protectRW, &protectOLD))
        {
            return false;
        }

        std::memcpy(address, data, length);

        if (!VirtualProtect(address, length, protectOLD, &protectRW))
        {
            return false;
        }

        return true;
    }

    inline std::string ExePath()
    {
        CHAR buffer[MAX_PATH] = { 0 };
        GetModuleFileNameA(NULL, buffer, MAX_PATH);

        std::string::size_type pos = std::string(buffer).find_last_of("\\/");

        return std::string(buffer).substr(0, pos);
    }
}