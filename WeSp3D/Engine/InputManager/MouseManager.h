#pragma once

#include "IInputManagerSubmodule.h"
#include "IModuleState.h"
#include "IErrorLogging.h"
#include "IUsesEngineAPI.h"

using namespace WeSp;

namespace WeSp 
{

class InputManager;

class MouseManager :
  public IInputManagerSubmodule, public IModuleState, public IErrorLogging, public IUsesEngineAPI
{
public:
  MouseManager() = delete;

  MouseManager(InputManager* pParentInstance);
  ~MouseManager();

  virtual bool Initialize(std::map<int, std::shared_ptr<IInputManagerSubmodule>> modules) override;
  virtual bool Terminate() override;
};

}