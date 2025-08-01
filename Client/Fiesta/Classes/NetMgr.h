#pragma once

#include "pch.h"

#include "Fiesta/Pointers.h"

namespace Fiesta::Classes
{
	class NetMgr
	{
		typedef void* (__thiscall* t_SendNetMsgWorldMgr)(void* self, unsigned short department, unsigned short command, void* pProto, int dataLength);
		inline static auto Original_SendNetMsgWorldMgr = reinterpret_cast<t_SendNetMsgWorldMgr>(Fiesta::Pointers::NetMgr::SendNetMsgWorldMgr);

	public:
		static void InstallHooks();
	private:
		void SendNetMsgWorldMgr(unsigned short department, unsigned short command, void* pProto, int dataLength);
	};
}