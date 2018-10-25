#pragma once

#include "common.h"
#include "BaseModule.h"

// Submodules.
#include "WindowManager.h"

using namespace WeSp;

namespace WeSp 
{

class RenderingManager :
  public BaseModule
{
public:
  RenderingManager() = delete;

  RenderingManager(BaseModule &parentModule);
  ~RenderingManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  std::shared_ptr<Window> ConstructWindow(eWindowType windowType, std::string windowTitle, size_t width, size_t height);

private:
  std::map<int, std::shared_ptr<BaseModule>> _subModules;
};

}
