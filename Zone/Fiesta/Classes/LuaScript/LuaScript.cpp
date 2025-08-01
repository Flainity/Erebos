#include "pch.h"
#include "LuaScript.h"

#include "Fiesta/Classes/ShineObjectManager/ShineObjectManager.h"
#include "Fiesta/Classes/ShineObjectManager/Pointers.h"

namespace Fiesta::Classes::LuaScript
{
    Structures::ShineObjectClass::ShinePlayer* LuaScript::GetPlayer(lua_State* lua_script)
    {
        const auto playerHandle = Original_ToNumber(lua_script, 1, nullptr);

        if (playerHandle < 8000 || playerHandle >= 9500) return nullptr;

        const auto player = reinterpret_cast<Structures::ShineObjectClass::ShinePlayer*>(
            ShineObjectManager::ShineObjectManager::Original_GetObject(
                ShineObjectManager::Pointers::ShineObjectManager, static_cast<unsigned short>(playerHandle)
            ));

        return player ? player : nullptr;
    }
}