#include "pch.h"
#include "Zone.h"

#include "Utility/Logging/FileLogger.h"
#include "Utility/HookRegistry.h"
#include "Utility/Configuration/Settings.h"

void Zone::SetupHooks()
{
    Utility::Configuration::Settings settings;
    Utility::Logging::FileLogger logger;
    
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    for (const auto& hook : Utility::GetHookRegistry())
    {
        if (settings.features.contains(hook.settingsKey))
        {
            if (settings.features[hook.settingsKey])
            {
                DetourAttach(hook.original, hook.hook);
                logger.Debug("Applying Hook for function: " + hook.name);
            }
        }
        else
        {
            logger.Warning("Skipping hook due to missing settings key");
            logger.Info("Missing settings key for feature: " + hook.settingsKey);
        }
    }

    DetourTransactionCommit();
}

void Zone::SetupPatches()
{
}