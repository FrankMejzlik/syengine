#pragma once

#include "EngineError.h"

using namespace SYE;

namespace SYE {

class IErrorLogging
{
public:
  IErrorLogging();
  virtual ~IErrorLogging();

  void PushEngineError(eEngineError type, size_t lineNumber, std::string filePath, std::string shortDescription = "", std::string longDescription = "");
  EngineError GetLastError();
  EngineError GetNextError();
  EngineError PopNextError();

protected:
  std::queue<EngineError> _engineErrorQueue;
};

}
