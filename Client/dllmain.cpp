#include "pch.h"

#include "Client.h"

auto APIENTRY DllMain(const HMODULE, const DWORD reason, LPVOID) -> BOOL
{
    if (reason != DLL_PROCESS_ATTACH) return true;

    Client::SetupHooks();
    Client::SetupPatches();

    return true;
}