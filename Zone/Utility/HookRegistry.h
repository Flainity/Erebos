#pragma once
#include <vector>
#include <string>

namespace Utility
{
    struct HookEntry
    {
        std::string name;
        std::string settingsKey;
        void** original;
        void* hook;
    };

    inline std::vector<HookEntry>& GetHookRegistry()
    {
        static std::vector<HookEntry> registry;
        return registry;
    }

    inline void RegisterHook(const std::string& name, const std::string& settingsKey, void** original, void* hook)
    {
        GetHookRegistry().push_back({ name, settingsKey, original, hook });
    }

    struct HookAutoRegister
    {
        HookAutoRegister(const std::string& name, const std::string& settingsKey, void** original, void* hook)
        {
            RegisterHook(name, settingsKey, original, hook);
        }
    };
}
