#include "pch.h"
#include "GameFrameWork.h"

namespace Fiesta::Classes::GameFrameWork
{
	void GameFrameWork::SendNetMsgWorldMgr(unsigned short department, unsigned short command, void* pProto, int dataLength)
	{
		Original_SendNetMsgWorldMgr(this, department, command, pProto, dataLength);
	}

	void GameFrameWork::AddNetMsgToWorldMgr(unsigned short department, unsigned short command)
	{
		Original_AddNetMsgToWorldMgr(this, department, command);
	}
}