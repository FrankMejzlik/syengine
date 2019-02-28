#pragma once

#include <string>
#include <queue>

namespace SYE {

/**
 * All possible error types in engine.
 *
 * 1 - 99     -> Critical errors -> Will terminate as soon as possible.
 * 100 - 499  -> Errors -> Will try to handle them.
 * 500 - 999  -> Warnings -> Notify user and try to solve them.
 * 1000+      -> Warnings to event that are supposed to happen
 *                e.g. Attaching duplicate Components, ...
 */
enum class eEngineError
{
  Null = 0,
  UnableToSetupMainModuleChannels = 1,
  SceneInitializationFailed = 2,

  UnableToLoadTextureFromFile = 500,
  MissingPointerToTargetWindowInstance = 501,
  PhysicalSceneNotSet = 502,
  PhysicsWorldNotSet = 503,
  PhysicsLibRaycastWeirdResult = 504,

  AttachingMultipleSingletonSlotComponents = 1000,
  DuplicateComponentOnEntity = 1001,
  OutOfRangeIndices = 1002
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