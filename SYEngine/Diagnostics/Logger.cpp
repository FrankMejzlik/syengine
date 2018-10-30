

#include <cstdio>
#include <exception>

#include "Logger.h"

using namespace SYE;

Logger* Logger::_pInstance = nullptr;

Logger* Logger::GetInstance()
{
	if (Logger::_pInstance == nullptr)
	{
		try
		{
			Logger::_pInstance = new Logger(GetCurrentProcessId());
		}
		catch (std::exception &e)
		{		
			printf("ERROR: Exception catched while instantiating Logger: %s\n", e.what());
		}
	}
	return Logger::_pInstance;
}

void Logger::Log(bool showTimestamp, eLogType logType,const char* format, ...) const
{
  // Define output file
  FILE* hOut = stdout;

  char prefix[4];

	switch (logType)
	{
  case eLogType::Error:
		Logger::GetInstance()->SetConsoleTextColour(eConsoleTextColour::Red);
    strcpy_s(prefix, sizeof(prefix), "E: ");
		break;
		
	case eLogType::Warning:
		Logger::GetInstance()->SetConsoleTextColour(eConsoleTextColour::Yellow);
    strcpy_s(prefix, sizeof(prefix), "W: ");
		break;

	case eLogType::Success:
		Logger::GetInstance()->SetConsoleTextColour(eConsoleTextColour::Green);
    strcpy_s(prefix, sizeof(prefix), "S: ");
		break;

  default:
    Logger::GetInstance()->SetConsoleTextColour(eConsoleTextColour::White);
    strcpy_s(prefix, sizeof(prefix), "I: ");
    break;
	}

  // Print timestamp
  if (showTimestamp)
  {
    float elapsedSeconds = static_cast<float>((float)clock() / CLOCKS_PER_SEC);

    printf("<%f> ", elapsedSeconds);
  }
  
  // Print prefix
  printf("%s", prefix);

  va_list ap;
  va_start(ap, format);
  vfprintf(hOut, format, ap);
  va_end(ap);
  printf("\n");

	Logger::GetInstance()->SetConsoleTextColour(eConsoleTextColour::White);
}


Logger::Logger(DWORD PID):
  _PID(PID), 
  _hStdOut(GetStdHandle(STD_OUTPUT_HANDLE))
{
  if (!_hStdOut)
  {
    printf("Error getting STDOUT handle!");
  }

  // Set default conosle colour to white
  SetConsoleTextColour(eConsoleTextColour::White);

}

Logger::~Logger() {}

bool Logger::SetConsoleTextColour(eConsoleTextColour colour)
{
  // Set colour to text
  if (!SetConsoleTextAttribute(_hStdOut, (WORD)colour))
  {
    return false;
  }
  return true;
}

