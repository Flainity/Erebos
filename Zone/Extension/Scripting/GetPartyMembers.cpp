#include "pch.h"
#include "GetPartyMembers.h"

#include "Fiesta/Classes/LuaScript/LuaScript.h"

namespace Extension::Scripting
{
    const char* GetPartyMembers::Command = "cGetPartyMembers";
    
    int GetPartyMembers::Execute(lua_State* lua_script)
    {
        const auto player = Fiesta::Classes::LuaScript::LuaScript::GetPlayer(lua_script);
        
        if (player == nullptr) return 0;

        const auto partyRegist = player->vtable->GetPartyRegistNumber(player);

        if (partyRegist == 65535u)
        {
            Fiesta::Classes::LuaScript::LuaScript::Original_PushNumber(lua_script, 0);
            Fiesta::Classes::LuaScript::LuaScript::Original_PushNumber(lua_script, player->vtable->GetZoneHandle(player));
				
            return 2;
        }

        const auto numberOfPlayers = player->PartyMemberInform.PartySlot->NumberOfMember;

        Fiesta::Classes::LuaScript::LuaScript::Original_PushNumber(lua_script, 1);

        for (auto i = 0; i < numberOfPlayers; ++i)
        {
            Fiesta::Classes::LuaScript::LuaScript::Original_PushNumber(lua_script, player->PartyMemberInform.PartySlot->Members[i].MemberInfo.Member.ZoneHandle);
        }
        
        return numberOfPlayers + 1;
    }
}