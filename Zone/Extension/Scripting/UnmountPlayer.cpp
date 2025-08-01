#include "pch.h"
#include "UnmountPlayer.h"

#include "Fiesta/Classes/LuaScript/LuaScript.h"

namespace Extension::Scripting
{
    const char* UnmountPlayer::Command = "cUnmountPlayer";
    
    int UnmountPlayer::Execute(lua_State* lua_script)
    {
        const auto player = Fiesta::Classes::LuaScript::LuaScript::GetPlayer(lua_script);
        
        if (player == nullptr) return 0;

        player->vtable->Org_so_MoverSystem_GetOff(player, 0);

        return 0;
    }
}