#include "pch.h"
#include "GetMobIndex.h"

#include "Fiesta/Classes/LuaScript/LuaScript.h"
#include "Fiesta/Classes/ShineObjectManager/ShineObjectManager.h"
#include "Fiesta/Classes/ShineObjectManager/Pointers.h"

namespace Extension::Scripting
{
    const char* GetMobIndex::Command = "cGetMobIndex";
    
    int GetMobIndex::Execute(lua_State* lua_script)
    {
        const auto mobHandle = Fiesta::Classes::LuaScript::LuaScript::Original_ToNumber(lua_script, 1, nullptr);
        const auto monster = Fiesta::Classes::ShineObjectManager::ShineObjectManager::Original_GetObject(Fiesta::Classes::ShineObjectManager::Pointers::ShineObjectManager, static_cast<unsigned short>(mobHandle));

        if (monster != nullptr)
        {
            const auto indexName = monster->vtable->GetInxName(monster);
            Fiesta::Classes::LuaScript::LuaScript::Original_PushString(lua_script, indexName);
            return 1;
        }

        return 0;
    }
}