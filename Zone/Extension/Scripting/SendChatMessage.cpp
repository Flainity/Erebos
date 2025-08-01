#include "pch.h"
#include "SendChatMessage.h"

#include "Fiesta/Classes/LuaScript/LuaScript.h"
#include "Fiesta/Classes/ShineObjectManager/ShineObjectManager.h"
#include "Fiesta/Classes/ShineObjectManager/Pointers.h"

namespace Extension::Scripting
{
    const char* SendChatMessage::Command = "cSendChatMessage";
    
    int SendChatMessage::Execute(lua_State* lua_script)
    {
        const auto mobHandle = Fiesta::Classes::LuaScript::LuaScript::Original_ToNumber(lua_script, 1, nullptr);
        const auto monster = Fiesta::Classes::ShineObjectManager::ShineObjectManager::Original_GetObject(Fiesta::Classes::ShineObjectManager::Pointers::ShineObjectManager, static_cast<unsigned short>(mobHandle));

        if (monster != nullptr)
        {
            const auto message = Fiesta::Classes::LuaScript::LuaScript::Original_ToString(lua_script, 2, nullptr);
            monster->vtable->Org_so_Chat(monster, 0xFFFFu, const_cast<char*>(message), strlen(message), true, 0);
            return 0;
        }

        return 0;
    }
}