#pragma once

namespace SYE 
{

// Forward declarations
class SceneContext;


/**
 * Interface for classes that needs to access EngineContext data
 *
 * This class is NOT responsible for allocation, only provides common API to it.
 */
class ISceneContextInterface
{
public:
  ISceneContextInterface() = delete;
  ISceneContextInterface(SceneContext* pSceneContext);

  SceneContext* GetSceneContextPtr() const { return _pSceneContext; };

private:
  SceneContext* _pSceneContext;
};

}