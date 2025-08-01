#pragma once

#include "pch.h"

#include "Fiesta/Classes/GameFrameWork/Pointers.h"
#include "Fiesta/Classes/GameFrameWork/Types.h"

namespace Fiesta::Classes::GameFrameWork
{
	class GameFrameWork
	{
		void SendNetMsgWorldMgr(unsigned short department, unsigned short command, void* pProto, int dataLength);
		void AddNetMsgToWorldMgr(unsigned short department, unsigned short command);

		SIGNATURE Original_SendNetMsgWorldMgr = reinterpret_cast<Types::t_SendNetMsgWorldMgr>(Pointers::SendNetMsgWorldMgr);
		SIGNATURE Original_AddNetMsgToWorldMgr = reinterpret_cast<Types::t_AddNetMsgToWorldMgr>(Pointers::AddNetMsgToWorldMgr);
	};
}