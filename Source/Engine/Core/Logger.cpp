#include "Logger.h"
#include <iostream>
#include "fileIO.h"

namespace kda {

	bool Logger::log(LogLevel logLevel, const std::string fileName, int line) {
		if (logLevel < m_logLevel) return false;
		switch (m_logLevel) {
			case LogLevel::Info:
				*this << "Info: ";
				break;
			case LogLevel::Warning:
				*this << "Warning: ";
				break;
			case LogLevel::Error:
				*this << "Error: ";
				break;
			case LogLevel::Assert:
				*this << "Assert: ";
				break;
				default: break;
		}	
		*this << getFileName(fileName) << "(" << line << ") ";

		return true;
	}
}