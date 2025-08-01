#pragma once

#include "pch.h"

#include "Pointers.h"
#include "Types.h"

#include "Fiesta/Templates.h"

namespace Fiesta::Classes::PgNet
{
	class PgNet
	{
	public:
		// Original Function Signature
		SIGNATURE Original_SendNetMsg = reinterpret_cast<Types::t_SendNetMsg>(Pointers::SendNetMsg);

	private:
		// Hook Functions
		void SendNetMsg(void* pdata, int length);

		// Hook Registration
		// REGISTER_HOOK("PgNet_SendNetMsg", Original_SendNetMsg, SendNetMsg)
	};
}
