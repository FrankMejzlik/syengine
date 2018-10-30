#pragma once

#include <vector>

#include "common.h"
#include "BaseModule.h"
#include "Window.h"

using namespace SYE;

namespace SYE 
{

class WindowManager :
  public BaseModule
{
public:
  WindowManager() = delete;

  WindowManager(BaseModule &parentModule);
  ~WindowManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;


  std::shared_ptr<Window> ConstructWindow(eWindowType windowType, std::string windowTitle, size_t width, size_t height);

private:
  std::vector<std::shared_ptr<Window>> _activeWindows;
};

}
