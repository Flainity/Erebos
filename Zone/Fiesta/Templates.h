#pragma once
#include <string>
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

    inline std::string ExePath()
    {
        CHAR buffer[MAX_PATH] = { 0 };
        GetModuleFileNameA(NULL, buffer, MAX_PATH);

        std::string::size_type pos = std::string(buffer).find_last_of("\\/");

        return std::string(buffer).substr(0, pos);
    }

    inline bool PatchMemory(void* address, void* data, int length)
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

    template <class T, class RT, class A1> _declspec(naked) RT __stdcall CallMemberFunction(UINT32 func, T* self, A1 arg1) {
        _asm {
            POP EAX
            ADD ESP, 0x8
            MOV ECX, DWORD PTR DS : [ESP - 0x4]
            PUSH EAX
            MOV EAX, DWORD PTR DS : [ESP - 0x4]
            JMP EAX
        }
    }
}