#include "Logger.h"
#include <iostream>
#include "fileIO.h"

namespace kda
{
	Logger g_logger(LogLevel::Info, &std::cout, "log.txt");

	bool Logger::Log(LogLevel logLevel, const std::string filename, int line)
	{
		if (logLevel < m_logLevel) return false;

		switch (logLevel)
		{
		case kda::Info:
			*this << "INFO: ";
			break;
		case kda::Warning:
			*this << "WARNING: ";
			break;
		case kda::Error:
			*this << "ERROR ";
			break;
		case kda::Assert:
			*this << "ASSERT: ";
			break;
		default:
			break;
		}

		*this << getFileName(filename) << "(" << line << ") ";

		return true;
	}
}