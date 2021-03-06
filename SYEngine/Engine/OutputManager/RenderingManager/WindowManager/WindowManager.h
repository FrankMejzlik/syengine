#pragma once

#include <map>
#include <memory>

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

  WindowManager(BaseModule& parentModule, EngineContext* pEngineContext);
  ~WindowManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;


  Window* ConstructWindow(eWindowType windowType, std::string_view windowTitle, size_t width, size_t height);
  bool DestroyWindow(Window* pWindow);

private:
  std::map< size_t, std::unique_ptr<Window> > _windows;
};

}
