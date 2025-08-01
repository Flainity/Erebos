#include "pch.h"
#include "NetMgr.h"

#include <string>

#include "Fiesta/Pointers.h"
#include "Fiesta/Structures.h"

#include "Utility/Logging/FileLogger.h"

namespace Fiesta::Classes
{
	void NetMgr::SendNetMsgWorldMgr(unsigned short department, unsigned short command, void* pProto, int dataLength)
	{
		Utility::Logging::FileLogger logger;
		logger.Debug("Sending Net Message to World Manager");
		const auto rdepartment = department << 10;
		logger.Debug(std::to_string(department));
		logger.Debug(std::to_string(rdepartment));
		logger.Debug(std::to_string(command));
		logger.Debug(std::to_string(command & 0x3FF));

		NetMgr::Original_SendNetMsgWorldMgr(this, department, command, pProto, dataLength);
	}

	void NetMgr::InstallHooks()
	{
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&reinterpret_cast<PVOID&>(NetMgr::Original_SendNetMsgWorldMgr), MemberFunc(NetMgr::SendNetMsgWorldMgr));
		DetourTransactionCommit();
	}
}