#pragma once

#include "ISimulationManagerSubmodule.h"
#include "IModuleState.h"
#include "IErrorLogging.h"
#include "IUsesEngineAPI.h"

namespace WeSp
{

class SimulationManager;

class LogicManager:
  public ISimulationManagerSubmodule, public IModuleState, public IErrorLogging, public IUsesEngineAPI
{
public:
  LogicManager() = delete;

  LogicManager(SimulationManager* pParentInstance);
  ~LogicManager();

  virtual bool Initialize(std::map<int, std::shared_ptr<ISimulationManagerSubmodule>> modules) override;
  virtual bool Terminate() override;
};

}