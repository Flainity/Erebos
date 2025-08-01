#pragma once

#include "pch.h"

#include "Fiesta/Structures.h"

namespace Fiesta::Classes::SkillInfoWin::Types
{
    typedef int (__thiscall* t_SetSkillInfo)(void* self, unsigned short skillId, bool viewEmpowerPointApplies, void* virtualValue, bool buy);
    typedef void* (__thiscall* t_HideAllMoneyWin)(void* self);
    typedef void* (__thiscall* t_SetSetItem)(void* self, unsigned short skillId);
    typedef int* (__thiscall* t_SetMinMaxWCRate)(void* self, ActiveSkillInfo* activeSkillInfo, int index);
    typedef int* (__thiscall* t_SetMinMaxMARate)(void* self, ActiveSkillInfo* activeSkillInfo, int index);
    typedef void* (__thiscall* t_SetTextBeginNewLine)(void* self, const char* textData, int* index, D3DXCOLOR* color);
    typedef char* (__thiscall* t_IsPassiveEffect)(void* self, unsigned short skillId, char* effectRate);
    typedef char* (__thiscall* t_FindPassiveEffect)(void* self, unsigned short skillId, char* effectRate);
    typedef void* (__thiscall* t_SetSetItemDesc)(void* self, int* index);
    typedef int* (__thiscall* t_SetPassiveEffect)(void* self, unsigned short skillId, int index);
}
