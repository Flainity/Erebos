#include "pch.h"
#include "GetChargeItem.h"

#include <string>

#include "Fiesta/Classes/LuaScript/LuaScript.h"

namespace Extension::Scripting
{
    const char* GetChargeItem::Command = "cGetChargeItem";
    
    int GetChargeItem::Execute(lua_State* lua_script)
    {
        const auto player = Fiesta::Classes::LuaScript::LuaScript::GetPlayer(lua_script);
        if (player == nullptr) return 0;

        const auto itemIndex = Fiesta::Classes::LuaScript::LuaScript::Original_ToString(lua_script, 2, nullptr);
        const auto& chargeItems = player->premium_items.list;

        for (const auto& effectItem : chargeItems.elements)
        {
            if (effectItem.item == nullptr) continue;

            if (std::string(effectItem.item->index) == itemIndex)
            {
                Fiesta::Classes::LuaScript::LuaScript::Original_PushBoolean(lua_script, true);
                return 1;
            }
        }

        Fiesta::Classes::LuaScript::LuaScript::Original_PushBoolean(lua_script, false);
        return 1;
    }
}