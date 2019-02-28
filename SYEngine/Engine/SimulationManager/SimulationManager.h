#pragma once

#include "BaseModule.h"
#include "Scene.h"

#include "PhysicsManager.h"

using namespace SYE;

namespace SYE 
{

class RenderingManager;

class SimulationManager :
  public BaseModule
{
public:
  SimulationManager() = delete;

  SimulationManager(BaseModule& parentModule, EngineContext* pEngineContext);
  ~SimulationManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  bool InitializeScene(Scene* pScene);
  void ProcessScene(dfloat deltaTime, Scene* pScene);

private:
};

}