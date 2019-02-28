
#include "IErrorLogging.h"

using namespace SYE;


IErrorLogging::IErrorLogging()
{}


IErrorLogging::~IErrorLogging()
{}

void IErrorLogging::PushEngineError(eEngineError type, std::string filePath, size_t lineNumber, std::string shortDescription, std::string longDescription) const
{
  _engineErrorQueue.push(EngineError(type, lineNumber, filePath, shortDescription, longDescription));
  return;
}

EngineError IErrorLogging::GetLastError() const
{
  return _engineErrorQueue.back();
}

EngineError IErrorLogging::GetNextError() const
{
  return _engineErrorQueue.front();
}

EngineError IErrorLogging::PopNextError() const
{
  EngineError retValue(_engineErrorQueue.front());
  _engineErrorQueue.pop();
  return retValue;
}
