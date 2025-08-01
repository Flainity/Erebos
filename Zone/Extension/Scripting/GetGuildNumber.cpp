#include "pch.h"
#include "GetGuildNumber.h"

#include "Fiesta/Classes/LuaScript/LuaScript.h"

namespace Extension::Scripting
{
    const char* GetGuildNumber::Command = "cGetGuildNumber";
    
    int GetGuildNumber::Execute(lua_State* lua_script)
    {
        const auto player = Fiesta::Classes::LuaScript::LuaScript::GetPlayer(lua_script);
        
        if (player == nullptr) return 0;

        const auto guildNumber = static_cast<int>(player->vtable->GetGuildNumber(player));
        
        Fiesta::Classes::LuaScript::LuaScript::Original_PushNumber(lua_script, guildNumber);
        return 1;
    }
}