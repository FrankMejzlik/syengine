#pragma once

#include <vector>

#include "common.h"
#include "BaseModule.h"

// Submodules.
#include "RenderingManager.h"
#include "AudioManager.h"
//#include "OtherInputManager.h"

using namespace WeSp;

namespace WeSp 
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

  std::shared_ptr<Window> ConstructWindow(eWindowType windowType, std::string windowTitle, size_t width, size_t height);


private:
 
};

}