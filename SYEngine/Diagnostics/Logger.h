#pragma once

/**
 * Implementation of Logger class.
 *
 * WARNING: This is Windows specific implementation.
 */

#include <Windows.h>
#undef APIENTRY
#include <cstdio>
#include <exception>
#include <string>
#include <ctime>

#include "config_engine.h"

#if LOG_DEV
  #define DLog(type, format, ...)  Logger::GetInstance()->Log(true, type, format, __VA_ARGS__); 
#else 
  #define DLog(type, format, ...)
#endif

namespace SYE
{

enum class eConsoleTextColour
{
	Black = 0,
	Blue = 1,
	Red = FOREGROUND_RED | FOREGROUND_INTENSITY,
	Orange = 0xC6,
	Green = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	Yellow = 14,
	White = 15
};

enum class eLogType
{
	Error,
	Warning,
	Info,
	Success
};

class Logger
{
public:
  Logger() = delete;
	static Logger* GetInstance();

	void Log(bool showTimestamp, eLogType logType, const char* format, ...) const;

private:
	static Logger* _pInstance;
  unsigned long _PID;

  // Console window handle
  void* _hStdOut;

	Logger(unsigned long PID);
	~Logger();

	bool SetConsoleTextColour(eConsoleTextColour colour);
};

}