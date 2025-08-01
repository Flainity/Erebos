#include "pch.h"
#include "SkillInfoWin.h"

#include "Utility/Logging/FileLogger.h"

namespace Fiesta::Classes::SkillInfoWin
{
    int SkillInfoWin::SetSkillInfo(unsigned short skillId, bool viewEmpowerPointApplies, void* virtualValue, bool buy)
    {
        Original_HideAllMoneyWin(this);
        auto windowText = this->m_apkTextWin;

        if (skillId == 0xFFFF) return 0;

        Original_SetSetItem(this, skillId);

        if (skillId < 20000u)
        {
            
        }
        
        return Original_SetSkillInfo(this, skillId, viewEmpowerPointApplies, virtualValue, buy);
    }
}