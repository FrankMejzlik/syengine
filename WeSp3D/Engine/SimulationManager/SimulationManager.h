#pragma once

#include "IMainEngineModule.h"
#include "IModuleState.h"
#include "IErrorLogging.h"
#include "IUsesEngineAPI.h"

#include "AIManager.h"
#include "LogicManager.h"
#include "PhysicsManager.h"

using namespace WeSp;

namespace WeSp {

class SimulationManager :
  public IMainEngineModule, public IModuleState, public IErrorLogging, public IUsesEngineAPI
{
public:
  SimulationManager() = delete;

  SimulationManager(Engine* pParentInstance);
  ~SimulationManager();

  virtual bool Initialize(std::map<int, std::shared_ptr<IMainEngineModule>> modules) override;
  virtual bool Terminate() override;

private:
  std::map<int, std::shared_ptr<ISimulationManagerSubmodule>> _subModules;
};

}