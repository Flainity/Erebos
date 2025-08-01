#include "pch.h"
#include "Revival.h"

#include "Fiesta/Classes/LuaScript/LuaScript.h"

namespace Extension::Scripting
{
    const char* Revival::Command = "cRevival";
    
    int Revival::Execute(lua_State* lua_script)
    {
        const auto player = Fiesta::Classes::LuaScript::LuaScript::GetPlayer(lua_script);
        
        if (player == nullptr) return 0;

        player->vtable->ReviveByItem(player);

        return 0;
    }
}