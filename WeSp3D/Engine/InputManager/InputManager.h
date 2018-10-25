#pragma once


#include "BaseModule.h"

// Include submodules
#include "KeyboardManager.h"
#include "MouseManager.h"
#include "ControllerManager.h"

using namespace WeSp;

namespace WeSp {

class InputManager:
  public BaseModule
{
public:
  InputManager() = delete;

  InputManager(BaseModule &parentModule);
  ~InputManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;


private:

};

}