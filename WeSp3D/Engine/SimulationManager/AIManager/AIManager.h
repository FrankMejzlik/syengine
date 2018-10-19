#pragma once

#include "ISimulationManagerSubmodule.h"
#include "IModuleState.h"
#include "IErrorLogging.h"
#include "IUsesEngineAPI.h"

namespace WeSp
{

class SimulationManager;

class AIManager:
  public ISimulationManagerSubmodule, public IModuleState, public IErrorLogging, public IUsesEngineAPI
{
public:
  AIManager() = delete;

  AIManager(SimulationManager* pParentInstance);
  ~AIManager();

  virtual bool Initialize(std::map<int, std::shared_ptr<ISimulationManagerSubmodule>> modules) override;
  virtual bool Terminate() override;
};

}