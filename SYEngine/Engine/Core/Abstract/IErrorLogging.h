#pragma once

#include "EngineError.h"


#define PUSH_ENGINE_ERROR(type, shortDesc, longDesc)  PushEngineError(type, __FILE__, __LINE__, shortDesc, longDesc); DLog(eLogType::Error, "%s", std::string(shortDesc).c_str())
#define PUSH_EDITOR_ERROR(type, shortDesc, longDesc)  PushEngineError(type, __FILE__, __LINE__, shortDesc, longDesc); DLog(eLogType::Error, "%s", std::string(shortDesc).c_str())

using namespace SYE;

namespace SYE 
{

class IErrorLogging
{
public:
  IErrorLogging();
  virtual ~IErrorLogging() noexcept;

  void PushEngineError(
    eEngineError type, 
    std::string filePath, size_t lineNumber, 
    std::string shortDescription = "", std::string longDescription = ""
  ) const;
  EngineError GetLastError() const;
  EngineError GetNextError() const;
  EngineError PopNextError() const;

protected:
  mutable std::queue<EngineError> _engineErrorQueue;
};

}
