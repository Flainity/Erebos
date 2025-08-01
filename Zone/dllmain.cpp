#include "pch.h"
#include "Zone.h"

auto APIENTRY DllMain(const HMODULE, const DWORD reason, LPVOID) -> BOOL
{
    if (reason != DLL_PROCESS_ATTACH) return true;

    Zone::SetupHooks();
    Zone::SetupPatches();

    return true;
}