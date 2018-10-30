#pragma once

#include <vector>

#include "common.h"
#include "BaseModule.h"
#include "Scene.h"

// Submodules.
#include "RenderingManager.h"
#include "AudioManager.h"
//#include "OtherInputManager.h"

using namespace SYE;

namespace SYE 
{

class Window;

class OutputManager :
  public BaseModule
{
public:
  OutputManager() = delete;

  OutputManager(BaseModule &parentModule);
  ~OutputManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  void ProcessScene(dfloat deltaTime, std::shared_ptr<Scene> pScene, std::shared_ptr<Window> pTargetWindow);
  std::shared_ptr<Window> ConstructWindow(eWindowType windowType, std::string windowTitle, size_t width, size_t height);


private:
  
};

}