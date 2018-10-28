#pragma once

#include "BaseModule.h"
#include "Scene.h"


namespace WeSp
{

class SimulationManager;

class LogicManager:
  public BaseModule
{
public:
  LogicManager() = delete;

  LogicManager(BaseModule &parentModule);
  ~LogicManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  void ProcessScene(dfloat deltaTime, std::shared_ptr<Scene> pScene);
};

}