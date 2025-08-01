#include "pch.h"
#include "GetEquippedWeaponType.h"

#include <string>

#include "Fiesta/Classes/LuaScript/LuaScript.h"
#include "Fiesta/Classes/ItemDataBox/ItemDataBox.h"
#include "Fiesta/Classes/ItemDataBox/Pointers.h"

namespace Extension::Scripting
{
    const char* GetEquippedWeaponType::Command = "cGetEquippedWeaponType";
    
    int GetEquippedWeaponType::Execute(lua_State* lua_script)
    {
        const auto player = Fiesta::Classes::LuaScript::LuaScript::GetPlayer(lua_script);
        
        if (player == nullptr) return 0;

        const auto weaponCell = player->sp_WeaponCell;

        if (weaponCell == nullptr)
        {
            Fiesta::Classes::LuaScript::LuaScript::Original_PushNumber(lua_script, 0);
            return 1;
        }

        const auto item = Fiesta::Classes::ItemDataBox::ItemDataBox::Original_ArrayOperator(Fiesta::Classes::ItemDataBox::Pointers::ItemDataBox, weaponCell->ItemInformation.Structure.ItemID);

        Fiesta::Classes::LuaScript::LuaScript::Original_PushNumber(lua_script, item->data->WeaponType);
        return 1;
    }
}