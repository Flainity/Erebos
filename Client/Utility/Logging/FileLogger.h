#pragma once

#include "pch.h"

#include <chrono>
#include <fstream>
#include <format>

#include "BaseLogger.h"
#include "Fiesta/Templates.h"

namespace Utility::Logging
{
	class FileLogger : public BaseLogger
	{
	public:
		void Debug(const std::string& message) override { AddLog("Client", "Debug", message); }
		void Info(const std::string& message) override { AddLog("Client", "Info", message); }
		void Success(const std::string& message) override { AddLog("Client", "Success", message); }
		void Warning(const std::string& message) override { AddLog("Client", "Warning", message); }
		void Error(const std::string& message) override { AddLog("Client", "Error", message); }
		void Exception(const std::string& message) override { AddLog("Client", "Exception", message); }
	private:
		void AddLog(const char* fileName, const char* type, const std::string& message) override
		{
            auto now = std::chrono::system_clock::now();
            std::time_t now_c = std::chrono::system_clock::to_time_t(now);
            std::tm now_tm{};
            localtime_s(&now_tm, &now_c);

            std::ostringstream dateStream;
            dateStream << std::put_time(&now_tm, "_%Y-%m-%d");

            const auto zoneNumber = 0;

            const auto path = Fiesta::Templates::ExePath() + R"(\)" + fileName + dateStream.str() + ".log";

            std::ostringstream logStream;
            logStream << "[" << std::put_time(&now_tm, "%T") << "] "
                << "[" << type << "] - "
                << "Client" << " - "
                << message;

            std::ofstream stream(path, std::ios_base::app);
            stream << logStream.str() << '\n';
            stream.close();
		}
	};
}