
#include "IErrorLogging.h"

using namespace WeSp;


IErrorLogging::IErrorLogging()
{}


IErrorLogging::~IErrorLogging()
{}

void IErrorLogging::PushEngineError(eEngineError type, size_t lineNumber, std::string filePath, std::string shortDescription, std::string longDescription)
{
  _engineErrorQueue.push(EngineError(type, lineNumber, filePath, shortDescription, longDescription));
  return;
}

EngineError IErrorLogging::GetLastError()
{
  return _engineErrorQueue.back();
}

EngineError IErrorLogging::GetNextError()
{
  return _engineErrorQueue.front();
}

EngineError IErrorLogging::PopNextError()
{
  EngineError retValue(_engineErrorQueue.front());
  _engineErrorQueue.pop();
  return retValue;
}