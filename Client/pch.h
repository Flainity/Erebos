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

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <detours.h>

#include "Utility/HookRegistry.h"

#define REGISTER_HOOK(name, orig, hookfunc) \
    inline static Utility::HookAutoRegister _auto_##orig { \
        name, reinterpret_cast<void**>(&(orig)), reinterpret_cast<void*>(MemberFunc(hookfunc)) \
    };

#ifdef _MSC_VER
    #define ALIGN(x) __declspec(align(x))
#else
    #define ALIGN(x) alignas(x)
#endif

#endif