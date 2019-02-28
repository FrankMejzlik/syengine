#pragma once

#include <vector>

#include "common.h"
#include "BaseModule.h"
#include "Scene.h"

#include "RenderingManager.h"
#include "AudioManager.h"

using namespace SYE;

namespace SYE 
{

class Window;

class OutputManager :
  public BaseModule
{
public:
  OutputManager() = delete;

  OutputManager(BaseModule &parentModule, EngineContext* pEngineContext);
  ~OutputManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  bool InitializeScene(Scene* pScene);
  void ProcessScene(dfloat deltaTime, Scene* pScene, Window* pTargetWindow);
  
  Window* ConstructWindow(eWindowType windowType, std::string_view windowTitle, size_t width, size_t height);


private:
  
};

}