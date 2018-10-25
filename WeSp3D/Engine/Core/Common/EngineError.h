#pragma once

#include <string>
#include <queue>

namespace WeSp {

/**
 * All possible error types in engine.
 */
enum class eEngineError
{
  Null = 0,
  UnableToSetupMainModuleChannels = 1
};

class EngineError
{
public:
  EngineError() = delete;
  
  EngineError(eEngineError type, size_t lineNumber, std::string filePath, std::string shortDescription, std::string longDescription);
  eEngineError GetType();
  size_t GetLineNumber();
  std::string GetFilePath();
  std::string GetShortDescription();
  std::string GetLongDescription();

private:
  eEngineError _type;
  size_t _lineNumber;
  std::string _filePath;
  std::string _shortDescription;
  std::string _longDescription;
};

}