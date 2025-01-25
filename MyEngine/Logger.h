#pragma once
#include <string>
#include <assert.h>


#if _DEBUG 
#define LOG_CONSOLE(logType,source,message)\
	Log::Logger::LogConsole(logType, source, message)
#define LOG_FILE(logType,source,message,path)\
	Log::Logger::LogFile(logType, source, message, path)
#define LOG_CONSOLE_ASSERT(expression ,logType,source,message)\
	if(!(expression))\
	{\
		Log::Logger::LogConsole(logType, source, message);\
		std::abort();\
	}
#define LOG_FILE_ASSERT(expr, logType, source, message, path)\
	if(!(expr)) { Log::Logger::LogFile(logType, source, message, path);\
	std::exit(EXIT_FAILURE);\
	}

#else 
#define LOG_CONSOLE(logType, source, message)
#endif // DEBUG

namespace Log {
	enum LogType {
		INFO,
		ERROR,
		WARNING,
	};
	class Logger
	{
	public:
		static std::string Log(LogType logType, std::string source, std::string message);
		static void LogConsole(LogType logType, std::string source, std::string message);
		static void LogFile(LogType logType, std::string source, std::string message, std::string logPath);

	private:
	};

}

