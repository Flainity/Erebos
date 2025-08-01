// ReSharper disable CppInconsistentNaming
#pragma once

#include "pch.h"

#include "Pointers.h"
#include "Types.h"

#include "Fiesta/Structures.h"
#include "Fiesta/Templates.h"

namespace Fiesta::Classes::SkillInfoWin
{
	class SkillInfoWin : public FrameBoxWin
	{
	public:
		SIGNATURE Original_SetSkillInfo = reinterpret_cast<Types::t_SetSkillInfo>(Pointers::SetSkillInfo);
		SIGNATURE Original_HideAllMoneyWin = reinterpret_cast<Types::t_HideAllMoneyWin>(Pointers::HideAllMoneyWin);
		SIGNATURE Original_SetSetItem = reinterpret_cast<Types::t_SetSetItem>(Pointers::SetSetItem);
		SIGNATURE Original_SetMinMaxWCRate = reinterpret_cast<Types::t_SetMinMaxWCRate>(Pointers::SetMinMaxWCRate);
		SIGNATURE Original_SetMinMaxMARate = reinterpret_cast<Types::t_SetMinMaxMARate>(Pointers::SetMinMaxMARate);
		SIGNATURE Original_SetTextBeginNewLine = reinterpret_cast<Types::t_SetTextBeginNewLine>(Pointers::SetTextBeginNewLine);
		SIGNATURE Original_IsPassiveEffect = reinterpret_cast<Types::t_IsPassiveEffect>(Pointers::IsPassiveEffect);
		SIGNATURE Original_FindPassiveEffect = reinterpret_cast<Types::t_FindPassiveEffect>(Pointers::FindPassiveEffect);
		SIGNATURE Original_SetSetItemDesc = reinterpret_cast<Types::t_SetSetItemDesc>(Pointers::SetSetItemDesc);
		SIGNATURE Original_SetPassiveEffect = reinterpret_cast<Types::t_SetPassiveEffect>(Pointers::SetPassiveEffect);

		PgWinText* m_apkTextWin[60];
		std::map<unsigned short, std::string> m_setItemName;
		PgWinSpr* m_pkGemIcon;
		PgWinSpr* m_pkGoldIcon;
		PgWinSpr* m_pkSilverIcon;
		PgWinSpr* m_pkCopperIcon;
		unsigned int m_uiIconWidth;
		unsigned int m_uiIconHeight;
		AutoSizingTextWin* m_pkGemText;
		AutoSizingTextWin* m_pkGoldText;
		AutoSizingTextWin* m_pkSilverText;
		AutoSizingTextWin* m_pkCopperText;
		int m_iFontHeight;

	private:
		int SetSkillInfo(unsigned short skillId, bool viewEmpowerPointApplies, void* virtualValue, bool buy);

		REGISTER_HOOK("SkillInfoWin::SetSkillInfo", Original_SetSkillInfo, SetSkillInfo)
	};
}
