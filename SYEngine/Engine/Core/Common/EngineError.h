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
  GraphicsApiInitializationFailed = 3,
  WindowInitialilzationFailed = 4,

  UnableToLoadTextureFromFile = 500,
  MissingPointerToTargetWindowInstance = 501,
  PhysicalSceneNotSet = 502,
  PhysicsWorldNotSet = 503,
  PhysicsLibRaycastWeirdResult = 504,
  CollisionWithoutColidingObjects = 505,
  IncompleteFrameBufferInRenderingToTextures = 506,
  LoadingShaderFileFailed = 507,
  FailedToCompileShaderProgram = 508,
  FailedToLinkShaderProgram = 509,
  ValidatingShaderFailed = 510,
  FailedToCreateShader = 515,
  UseShaderFailed = 516,
  FailedToGenerateShaderProgram = 517,
  FailedToLoadSystemShaders = 520,
  AttemptedToFillShaderUniformsWithoutParentComponent = 521,
  FailedToRenderMesh = 522,
 

  AttachingMultipleSingletonSlotComponents = 1000,
  DuplicateComponentOnEntity = 1001,
  OutOfRangeIndices = 1002,
  RegisteredAlreadyExistingComponentToScene = 1003,
  RegisteredAlreadyExistingChildComponentToScene = 1004,
  AddingEntityToSceneFailed = 1005,
  TryingToDeleteNonExistentEntityFromScene = 1006,
  UnableToDeleteEntityBecauseDestructionFailed = 1007,
  AddingComponentToEntityFailed = 1008,
  TryingToDeleteNonExistentComponentFromEntity = 1009,
  UnableToDeleteComponentBecauseDestructionFailed = 1010,
  AddingEntityToEntityFailed = 1011,
  AttachingAlreadyExistingEntityToEntity = 1012,
  AttachingAlreadyExistingEntityToScene = 1013,
  TryingToDeleteNonExistentEntityFromEntity = 1014,
  TryingToUseNonExistingTextureOnMaterial = 1015,
  GettingIdOfEmptyTexture = 1016,
  AddingAlreadyExistingShader = 1017,
  RenderingMeshWithoutParentMeshRenderer = 1018,
  ProcessingNonImplementedUniform = 1019,
  AttemptingToRenderSceneWithoutMainCameraAttached = 1020,
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