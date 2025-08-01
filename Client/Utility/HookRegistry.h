#pragma once
#include <vector>
#include <string>

namespace Utility
{
    struct HookEntry
    {
        std::string name;
        void** original;
        void* hook;
    };

    inline std::vector<HookEntry>& GetHookRegistry()
    {
        static std::vector<HookEntry> registry;
        return registry;
    }

    inline void RegisterHook(const std::string& name, void** original, void* hook)
    {
        GetHookRegistry().push_back({ name, original, hook });
    }

    struct HookAutoRegister
    {
        HookAutoRegister(const std::string& name, void** original, void* hook)
        {
            RegisterHook(name, original, hook);
        }
    };
}
