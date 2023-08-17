#pragma once
#include <string>
#include <cassert>
#include <fstream>
#include <iostream>
#include "Framework/Singleton.h"

#ifdef _DEBUG 
#define INFO_LOG(message)	{ if(kda::Logger::Instance().log(kda::LogLevel::Info, __FILE__, __LINE__))	{ kda::Logger::Instance() << message << "\n";} }
#define WARNING_LOG(message){ if(kda::Logger::Instance().log(kda::LogLevel::Warning, __FILE__, __LINE__)) { kda::Logger::Instance() << message << "\n";} }
#define ERROR_LOG(message)	{ if(kda::Logger::Instance().log(kda::LogLevel::Error, __FILE__, __LINE__))	{ kda::Logger::Instance() << message << "\n";} }
#define ASSERT_LOG(condition, message)	{ if(!condition && kda::Logger::Instance().log(kda::LogLevel::Assert, __FILE__, __LINE__)) { kda::Logger::Instance() << message << "\n";} assert(condition); }
#else
#define INFO_LOG(message)	{}
#define WARNING_LOG(message){}
#define ERROR_LOG(message)	{}
#define ASSERT_LOG(condition, message)	{}
#endif // _DEBUG

namespace kda {
	enum class LogLevel {
		Info,
		Warning,
		Error,
		Assert
	};

	class Logger : public Singleton<Logger>{
		public:
			Logger(LogLevel logLevel = LogLevel::Info, std::ostream* ostream = &std::cout, const std::string& filename = "Log.txt") :
				m_logLevel{ logLevel },
				m_ostream{ ostream } 
			{
				if(!filename.empty()) m_fstream.open(filename);
			}

			bool log(LogLevel logLevel, const std::string fileName, int line);

			template<typename T>
			Logger& operator << (T value);

		private:
			LogLevel m_logLevel;
			std::ostream* m_ostream = nullptr;
			std::ofstream m_fstream;
	};

	template<typename T>
	inline Logger& Logger::operator<<(T value) {
		if (m_ostream) *m_ostream << value;

		if (m_fstream.is_open()) {
			m_fstream << value;
			m_fstream.flush();
		}
		return *this;
	}
}