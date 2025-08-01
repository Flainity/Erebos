#pragma once

#define POINTER constexpr unsigned int
#define CAST_POINTER const static auto

namespace Fiesta::Pointers
{
    namespace Colors
    {
        POINTER White = 0xA695B0;
        POINTER Black = 0xA695C0;
        POINTER Red = 0xA695D0;
        POINTER Green = 0xA695E0;
        POINTER Blue = 0xA695F0;
        POINTER Yellow = 0xA69600;
        POINTER Gold = 0xA69610;
        POINTER Orange = 0xA69620;
        POINTER Gray = 0xA69630;
        POINTER Gray2 = 0xA69640;
        POINTER Purple = 0xA69650;
        POINTER Brown = 0xA69660;
        POINTER Pink = 0xA69670;
        POINTER LPText = 0xA69680;
    }
    
    namespace Globals
    {
        POINTER ClientName = 0x45C113;
        POINTER LogoutTimer = 0x5AAAE6;
        CAST_POINTER User = reinterpret_cast<void*>(0xA97090);
    }

    namespace User
    {
        constexpr unsigned int GetGold = 0x666AF0;
        constexpr unsigned int GetGem = 0x666AD0;
        constexpr unsigned int ConvertMoney = 0x666BE0;
        constexpr unsigned int AddCurrentExp = 0x666520;
    }

    namespace IDirectMessenger
    {
        POINTER SendDirectMessage = 0x409E90;
    }

    namespace CharDeadEvent
    {
        namespace ExpGain
        {
            POINTER OnDead = 0x614F10;
        }
    }

    namespace MoneyWin
    {
        constexpr unsigned int Create = 0x557EB3;
    }

    namespace TextData
    {
        POINTER Get = 0x408650;
    }

    namespace Generic
    {
        POINTER fs = 0x7391B0;
    }

    namespace GameFrameWork
    {
        POINTER NcUserPacketToWorld = 0x4A34C0;
        POINTER SendNetMsgWorldMgr = 0x4A18D0;
        POINTER AddNetMsgToWorldMgr = 0x4A1890;
    }

    namespace PgNet
    {
        POINTER SendNetMsg = 0x8CF200;
    }

    namespace NetMgr
    {
        POINTER SendNetMsgWorldMgr = 0x6D9F60;
    }
}