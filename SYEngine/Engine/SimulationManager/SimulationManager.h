#pragma once

#include "BaseModule.h"
#include "Scene.h"

#include "PhysicsManager.h"

using namespace SYE;

namespace SYE {

class SimulationManager :
  public BaseModule
{
public:
  SimulationManager() = delete;

  SimulationManager(BaseModule &parentModule);
  ~SimulationManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  void InitializePhysicsScene(std::shared_ptr<Scene> pScene);

  void ProcessScene(dfloat deltaTime, std::shared_ptr<Scene> pScene);

private:
};

}