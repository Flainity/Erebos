#include "pch.h"
#include "Client.h"

#include "Patches/ClientName.h"
#include "Patches/LevelDisplay.h"
#include "Patches/SkillFunctionColor.h"
#include "Patches/SkillWindowWidth.h"
#include "Patches/StatDisplay.h"
#include "Utility/HookRegistry.h"

void Client::SetupHooks()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	for (const auto& hook : Utility::GetHookRegistry())
	{
		DetourAttach(hook.original, hook.hook);
	}

	DetourTransactionCommit();
}

void Client::SetupPatches()
{
	Patches::ClientName::Install();
	Patches::SkillWindowWidth::Install();
	Patches::SkillFunctionColor::Install();
	Patches::LevelDisplay::Install();
	Patches::StatDisplay::Install();
}