#include "EngineError.h"

using namespace SYE;

EngineError::EngineError(eEngineError type, size_t lineNumber, std::string filePath, std::string shortDescription, std::string longDescription) :
  _type(type),
  _lineNumber(lineNumber),
  _filePath(filePath),
  _shortDescription(shortDescription),
  _longDescription(longDescription) 
{}

eEngineError EngineError::GetType()
{
  return _type;
}

size_t EngineError::GetLineNumber()
{
  return _lineNumber;
}
std::string EngineError::GetFilePath()
{
  return _filePath;
}

std::string EngineError::GetShortDescription()
{
  return _shortDescription;
}
std::string EngineError::GetLongDescription()
{
  return _longDescription;
}