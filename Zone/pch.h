#ifndef PCH_H
#define PCH_H

#define PUBLIC public:
#define PRIVATE private:
#define PROTECTED protected:

#define PUBLIC_STATIC public: static
#define PRIVATE_STATIC private: static
#define PROTECTED_STATIC protected: static

#define POINTER constexpr unsigned int
#define CAST_POINTER const static auto

#define SIGNATURE inline static auto

#define PACK( Declaration, Alignment ) __pragma( pack(push, Alignment) ) Declaration __pragma( pack(pop) )

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <detours.h>
#include <lua.h>

#define REGISTER_HOOK(name, settingsKey, orig, hookfunc) \
    inline static Utility::HookAutoRegister _auto_##orig { \
        name, settingsKey, reinterpret_cast<void**>(&(orig)), reinterpret_cast<void*>(MemberFunc(hookfunc)) \
    };

#endif