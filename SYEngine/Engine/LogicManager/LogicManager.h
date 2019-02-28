#pragma once

#include "BaseModule.h"

namespace SYE
{

class Scene;

class LogicManager:
  public BaseModule
{
public:
  LogicManager() = delete;

  LogicManager(BaseModule& parentModule, EngineContext* pEngineContext);
  ~LogicManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  bool InitializeScene(Scene* pScene);
  void ProcessScene(dfloat deltaTime, Scene* pScene);


};

}