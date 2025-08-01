// ReSharper disable CppClangTidyClangDiagnosticMicrosoftCast
#include "pch.h"
#include "LuaScriptScenario.h"

#include "Fiesta/Structures.h"
#include "Fiesta/Classes/LuaScript/LuaScript.h"

#include "Extension/Scripting/GetChargeItem.h"
#include "Extension/Scripting/GetEquippedWeaponType.h"
#include "Extension/Scripting/GetGuildNumber.h"
#include "Extension/Scripting/GetMobIndex.h"
#include "Extension/Scripting/GetPartyMembers.h"
#include "Extension/Scripting/Revival.h"
#include "Extension/Scripting/SendChatMessage.h"
#include "Extension/Scripting/ToggleFieldAttribute.h"
#include "Extension/Scripting/UnmountPlayer.h"

namespace Fiesta::Classes::LuaScriptScenario
{
    void LuaScriptScenario::AddCommand(const Structures::LuaScript* script, const char* command, void* function)
    {
        LuaScript::LuaScript::Original_PushClosure(script->ls_LuaObject, function, 0);
        LuaScript::LuaScript::Original_SetGlobal(script->ls_LuaObject, command);
    }

    char LuaScriptScenario::FuncSet()
    {
        const auto script = reinterpret_cast<Structures::LuaScript*>(this);
        const char returnValue = Original_FuncSet(this);

        AddCommand(script, Extension::Scripting::GetGuildNumber::Command, Extension::Scripting::GetGuildNumber::Execute);
        AddCommand(script, Extension::Scripting::GetMobIndex::Command, Extension::Scripting::GetMobIndex::Execute);
        AddCommand(script, Extension::Scripting::GetChargeItem::Command, Extension::Scripting::GetChargeItem::Execute);
        AddCommand(script, Extension::Scripting::GetEquippedWeaponType::Command, Extension::Scripting::GetEquippedWeaponType::Execute);
        AddCommand(script, Extension::Scripting::GetPartyMembers::Command, Extension::Scripting::GetPartyMembers::Execute);
        AddCommand(script, Extension::Scripting::Revival::Command, Extension::Scripting::Revival::Execute);
        AddCommand(script, Extension::Scripting::SendChatMessage::Command, Extension::Scripting::SendChatMessage::Execute);
        AddCommand(script, Extension::Scripting::ToggleFieldAttribute::Command, Extension::Scripting::ToggleFieldAttribute::Execute);
        AddCommand(script, Extension::Scripting::UnmountPlayer::Command, Extension::Scripting::UnmountPlayer::Execute);
        
        return returnValue;
    }
}
