#pragma once

#include "BaseModule.h"

using namespace SYE;

namespace SYE 
{

class Scene;

class ScriptManager :
  public BaseModule
{
public:
  ScriptManager() = delete;

  ScriptManager(BaseModule &parentModule);
  ~ScriptManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  void InitializeScene(Scene* pScene);
  void ProcessScene(dfloat deltaTime, Scene* pScene);


private:

};

}