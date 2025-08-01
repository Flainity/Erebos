#pragma once

#include <map>

#include "mini.h"
#include "Utility/Helper/TypeConverter.h"
#include "Fiesta/Templates.h"

namespace Utility::Configuration
{
    class Settings
    {
    public:
        std::map<std::string, bool> features = {
            {"ZoneResponder", false},
            {"AdminCommands", false},
            {"LuaCommands", false},
            {"ParameterChange", false}
        };
    
        struct Config
        {
            bool IsService;
            bool DebugMode;
        } configuration;

        struct Patches
        {
            int LogoutTimer;
        } patches;

        Settings()
        {
            const auto path = Fiesta::Templates::ExePath() + R"(\..\Hook\zone.ini)";
            const mINI::INIFile file(path);
            mINI::INIStructure settingsIni;
            file.read(settingsIni);

            configuration.IsService = Helper::TypeConverter::StringToBoolean(settingsIni["Debug"]["IsService"]);
            configuration.DebugMode = Helper::TypeConverter::StringToBoolean(settingsIni["Debug"]["DebugMode"]);

            features["ZoneResponder"] = Helper::TypeConverter::StringToBoolean(settingsIni["Features"]["ZoneResponder"]);
            features["AdminCommands"] = Helper::TypeConverter::StringToBoolean(settingsIni["Features"]["AdminCommands"]);
            features["LuaCommands"] = Helper::TypeConverter::StringToBoolean(settingsIni["Features"]["LuaCommands"]);
            features["ParameterChange"] = Helper::TypeConverter::StringToBoolean(settingsIni["Features"]["ParameterChange"]);

            patches.LogoutTimer = Helper::TypeConverter::StringToInt(settingsIni["Patches"]["LogoutTimer"]);
        }
    };
}
