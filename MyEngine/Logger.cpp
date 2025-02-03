#include "Logger.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <format>

std::string logTypeToString(Log::LogType logType) {
	switch (logType) {
	case Log::LogType::INFO:
		return "Info";
	case Log::LogType::WARNING:
		return "Warning";
	case Log::LogType::ERROR:
		return "Error";
	default:
		return "Unknown";
	}
}

std::string timeNow() {
	std::time_t result = std::time(NULL);
	char buffer[26]; 
	ctime_s(buffer, sizeof(buffer), &result);
	std::string datetime = std::string(buffer);
	datetime.pop_back();
	return datetime;
}


std::string Log::Logger::Log(LogType logType, std::string source, std::string message)
{
	return std::format("[{}] [{}] \"{}\" : {}", logTypeToString(logType), timeNow(), source, message);
}


void Log::Logger::LogConsole(LogType logType, std::string source, std::string message)
{
	std::cout << Log(logType, source, message) << std::endl;
}


void Log::Logger::LogFile(LogType logType, std::string source, std::string message, std::string logPath)
{
	std::ofstream logFile(logPath, std::ios::app);
	if(logFile)
		logFile << Log(logType, source, message) << std::endl;
	logFile.close();
}

