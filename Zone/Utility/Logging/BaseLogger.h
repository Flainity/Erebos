#pragma once

#include "pch.h"

#include <chrono>
#include <fstream>
#include <format>

namespace Utility::Logging
{
	class BaseLogger
	{
	public:
		virtual void Debug(const std::string& message) = 0;
		virtual void Info(const std::string& message) = 0;
		virtual void Success(const std::string& message) = 0;
		virtual void Warning(const std::string& message) = 0;
		virtual void Error(const std::string& message) = 0;
		virtual void Exception(const std::string& message) = 0;
	private:
		virtual void AddLog(const char* fileName, const char* type, const std::string& message) = 0;
	};
}