#pragma once


#if unix


/**
 * Implementation of Logger class.
 *
 * WARNING: This is Windows specific implementation.
 */

#include <cstdio>
#include <exception>
#include <string>
#include <ctime>
#include <memory>

#include "config_engine.h"

#if LOG_DEV
  #define DLog(type, format, ...)  Logger::GetInstance()->Log(true, type, __FILE__, __LINE__, format, __VA_ARGS__); 
#else 
  #define DLog(type, format, ...)
#endif

namespace SYE
{

enum class eConsoleTextColour
{
	Black = 0,
	Blue = 1,
	Red = 2,
	Orange = 0xC6,
	Green = 4,
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
  static Logger* GetInstance();

  Logger() = delete;
  Logger(unsigned long PID);
  ~Logger();
  

	void Log(bool showTimestamp, eLogType logType, std::string_view filename, int lineNumber, const char* format, ...) const;

private:
	static std::unique_ptr<Logger> _pInstance;
  unsigned long _PID;


	bool SetConsoleTextColour(eConsoleTextColour colour);
};

}

#endif



#if _WIN32

/**
 * Implementation of Logger class.
 *
 * WARNING: This is Windows specific implementation.
 */

#include <Windows.h>
#include <cstdio>
#include <exception>
#include <string>
#include <ctime>
#include <memory>

#include "config_engine.h"

#if LOG_DEV
  #define DLog(type, format, ...)  Logger::GetInstance()->Log(true, type, __FILE__, __LINE__, format, __VA_ARGS__); 
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
  static Logger* GetInstance();

  Logger() = delete;
  Logger(unsigned long PID);
  ~Logger();
  

	void Log(bool showTimestamp, eLogType logType, std::string_view filename, int lineNumber, const char* format, ...) const;

private:
	static std::unique_ptr<Logger> _pInstance;
  unsigned long _PID;

  // Console window handle
  void* _hStdOut;

	
	

	bool SetConsoleTextColour(eConsoleTextColour colour);
};

}

#endif
