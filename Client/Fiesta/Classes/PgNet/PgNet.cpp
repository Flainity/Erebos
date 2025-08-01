#include "pch.h"
#include "PgNet.h"

#include "Utility/Logging/FileLogger.h"

namespace Fiesta::Classes::PgNet
{
	void PgNet::SendNetMsg(void* pdata, int length)
	{
		Utility::Logging::FileLogger logger;
		logger.Debug("Called SendNetMsg");

		Original_SendNetMsg(this, pdata, length);
	}
}