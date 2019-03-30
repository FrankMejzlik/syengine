


#include "Logger.h"

using namespace SYE;

#if unix


std::unique_ptr<Logger> Logger::_pInstance = std::unique_ptr<Logger>(nullptr);

Logger* Logger::GetInstance()
{
	if (Logger::_pInstance == nullptr)
	{
		try
		{
			Logger::_pInstance = std::make_unique<Logger>(GetCurrentProcessId());
		}
		catch (std::exception &e)
		{		
			printf("ERROR: Exception catched while instantiating Logger: %s\n", e.what());
		}
	}
	return Logger::_pInstance.get();
}

void Logger::Log(bool showTimestamp, eLogType logType, std::string_view filename, int lineNumber, const char* format, ...) const
{
  // Define output file
  FILE* hOut = stdout;

  char prefix[4];

	switch (logType)
	{
  case eLogType::cError:
		Logger::GetInstance()->SetConsoleTextColour(eConsoleTextColour::Red);
    strcpy_s(prefix, sizeof(prefix), "E: ");
		break;
		
	case eLogType::cWarning:
		Logger::GetInstance()->SetConsoleTextColour(eConsoleTextColour::Yellow);
    strcpy_s(prefix, sizeof(prefix), "W: ");
		break;

	case eLogType::cSuccess:
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

  printf("| %s:%d", filename.data(), lineNumber);

  printf("\n");

	Logger::GetInstance()->SetConsoleTextColour(eConsoleTextColour::White);
}


Logger::Logger(unsigned long PID):
  _PID(PID)
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
  /*if (!SetConsoleTextAttribute(_hStdOut, (WORD)colour))
  {
    return false;
  }*/
  return true;
}



#endif

#if _WIN32


std::unique_ptr<Logger> Logger::_pInstance = std::unique_ptr<Logger>(nullptr);

Logger* Logger::GetInstance()
{
	if (Logger::_pInstance == nullptr)
	{
		try
		{
			Logger::_pInstance = std::make_unique<Logger>(GetCurrentProcessId());
		}
		catch (std::exception &e)
		{		
			printf("ERROR: Exception catched while instantiating Logger: %s\n", e.what());
		}
	}
	return Logger::_pInstance.get();
}

void Logger::Log(bool showTimestamp, eLogType logType, std::string_view filename, int lineNumber, const char* format, ...) const
{
  // Define output file
  FILE* hOut = stdout;

  char prefix[4];

	switch (logType)
	{
  case eLogType::cError:
		Logger::GetInstance()->SetConsoleTextColour(eConsoleTextColour::Red);
    strcpy_s(prefix, sizeof(prefix), "E: ");
		break;
		
	case eLogType::cWarning:
		Logger::GetInstance()->SetConsoleTextColour(eConsoleTextColour::Yellow);
    strcpy_s(prefix, sizeof(prefix), "W: ");
		break;

	case eLogType::cSuccess:
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

  printf("| %s:%d", filename.data(), lineNumber);

  printf("\n");

	Logger::GetInstance()->SetConsoleTextColour(eConsoleTextColour::White);
}


Logger::Logger(unsigned long PID):
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

#endif
