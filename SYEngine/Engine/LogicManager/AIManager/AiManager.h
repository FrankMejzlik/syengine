#pragma once

#include "BaseModule.h"

using namespace SYE;

namespace SYE 
{

class Scene;

class AiManager :
  public BaseModule
{
public:
  AiManager() = delete;

  AiManager(BaseModule& parentModule, EngineContext* pEngineContext);
  ~AiManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  void InitializeScene(Scene* pScene);
  void ProcessScene(dfloat deltaTime, Scene* pScene);

private:

};

}