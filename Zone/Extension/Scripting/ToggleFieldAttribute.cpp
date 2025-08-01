#include "pch.h"
#include "ToggleFieldAttribute.h"

#include "Fiesta/Classes/LuaScript/LuaScript.h"
#include "Fiesta/Classes/FieldContainer/FieldContainer.h"
#include "Fiesta/Classes/FieldContainer/Pointers.h"

#include "Utility/Logging/FileLogger.h"

namespace Extension::Scripting
{
    const char* ToggleFieldAttribute::Command = "cToggleFieldAttribute";
    
    int ToggleFieldAttribute::Execute(lua_State* lua_script)
    {
        Utility::Logging::FileLogger logger;
        
        const auto field = Fiesta::Classes::FieldContainer::FieldContainer::Original_FindMap(
            Fiesta::Classes::FieldContainer::Pointers::FieldContainer,
            Fiesta::Classes::LuaScript::LuaScript::Original_ToString(lua_script, 1, nullptr));
        
        const auto attribute = Fiesta::Classes::LuaScript::LuaScript::Original_ToString(lua_script, 2, nullptr);
        const auto value = Fiesta::Classes::LuaScript::LuaScript::Original_ToBoolean(lua_script, 3);

        if (field == nullptr)
        {
            logger.Error("Vision Hook :: ToggleFieldAttribute :: Field not found.");
        }

        if (field != nullptr)
        {
            const char active = value ? 1 : 0;
            const auto attributeString = std::string(attribute);

            if (attributeString == "Ride")
            {
                field->fm_FieldOption->byCanRide = active;
            }
            else if (attributeString == "Minihouse")
            {
                field->fm_FieldOption->byCanMiniHouset = active;
            }
            else if (attributeString == "Item")
            {
                field->fm_FieldOption->byCanItem = active;
            }
            else if (attributeString == "Skill")
            {
                field->fm_FieldOption->byCanSkill = active;
            }
            else if (attributeString == "Chat")
            {
                field->fm_FieldOption->byCanChat = active;
            }
            else if (attributeString == "Shout")
            {
                field->fm_FieldOption->byCanShout = active;
            }
            else if (attributeString == "Booth")
            {
                field->fm_FieldOption->byBooth = active;
            }
            else if (attributeString == "Produce")
            {
                field->fm_FieldOption->byProduce = active;
            }
            else if (attributeString == "Stone")
            {
                field->fm_FieldOption->canstoneuse = active;
            }
            else if (attributeString == "Party")
            {
                field->fm_FieldOption->canparty = active;
            }
            else if (attributeString == "Respawn")
            {
                field->fm_FieldOption->canrestart = active;
            }
            else if (attributeString == "Trade")
            {
                field->fm_FieldOption->cantrade = active;
            }
            else if (attributeString == "HideName")
            {
                field->fm_FieldOption->NameHide = active;
            }
            else
            {
                logger.Warning("Vision Hook :: ToggleFieldAttribute :: Unknown attribute: " + attributeString);
            }
        }

        return 0;
    }
}