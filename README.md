# Erebos
Erebos is an extension framework for the game Fiesta Online. It is meant to be used and maintained for other people 
to get started with reverse engineering and hooking for the game\
This project is the successor of [AuroraEX](https://github.com/Flainity/AuroraEX). Erebos is aimed to clarify
the structure of the base game even more. One of the most notable changes being the correct usage of namespaces 
and classes from the original source code.

---
## Registering a hook
Erebos currently uses a macro, which is defined in each projects [pch.h](Zone/pch.h) (Zone as exmaple) to automatically
register hook functions. This macro needs to be included in the respective .h file of the functionality. Use the
[LuaScriptScenario](Zone/Fiesta/Classes/LuaScriptScenario/LuaScriptScenario.h) hook as an example here.

The macro accepts 4 parameters in total.
```c++
void REGISTER_HOOK(name, settingsKey, orig, hookfunc)
```
**name** - should resemble the function you are overriding. This will be used in Debug logs.\
**settingsKey** - determines which configuration key should be checked from the settings file to determine if the hook is enabled or not.\
**orig** - pointer to the original function.\
**hookFunc** - pointer to the new function.

---
### ⚠️ Disclaimer
Erebos is only meant to be used for educational purposes. I do not support the use of this software for any case, that
is not legal.\
Please keep in mind, that using multiple game hooks may result in unexpected behaviour.
