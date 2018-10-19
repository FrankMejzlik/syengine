#pragma once

// Include interfaces
#include "IMainEngineModule.h"
#include "IModuleState.h"
#include "IErrorLogging.h"
#include "IUsesEngineAPI.h"

// Include submodules
#include "KeyboardManager.h"
#include "MouseManager.h"
#include "ControllerManager.h"

using namespace WeSp;

namespace WeSp {

class InputManager:
  public IMainEngineModule, public IModuleState, public IErrorLogging, public IUsesEngineAPI
{
public:
  InputManager() = delete;

  InputManager(Engine* pParentInstance);
  ~InputManager();

  virtual bool Initialize(std::map<int, std::shared_ptr<IMainEngineModule>> modules) override;
  virtual bool Terminate() override;


private:
  std::map<int, std::shared_ptr<IInputManagerSubmodule>> _subModules;
};

}