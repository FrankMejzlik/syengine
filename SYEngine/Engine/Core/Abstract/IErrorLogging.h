#pragma once

#include "EngineError.h"

#define PUSH_ENGINE_ERROR(type, shortDesc, longDesc)  PushEngineError(type, __FILE__, __LINE__, shortDesc, longDesc) 
#define PUSH_EDITOR_ERROR(type, shortDesc, longDesc)  PushEngineError(type, __FILE__, __LINE__, shortDesc, longDesc) 

using namespace SYE;

namespace SYE {

class IErrorLogging
{
public:
  IErrorLogging();
  virtual ~IErrorLogging();

  void PushEngineError(
    eEngineError type, 
    std::string filePath, size_t lineNumber, 
    std::string shortDescription = "", std::string longDescription = ""
  );
  EngineError GetLastError();
  EngineError GetNextError();
  EngineError PopNextError();

protected:
  std::queue<EngineError> _engineErrorQueue;
};

}
