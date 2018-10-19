#pragma once

#include <map>

#include "Logger.h"

namespace WeSp {

class SimulationManager;

/**
 * Interface for SimulationManager submodule. Giving it necessary things that modules must have.
 *
 * Giving it Initialize interface for setting up all common things (e.g. pointers to other module instances)
 */
class ISimulationManagerSubmodule
{
public:
  ISimulationManagerSubmodule() = delete;

  // Main modules can be childs only of SimulationManager class
  ISimulationManagerSubmodule(SimulationManager* pParentInstance);
  virtual ~ISimulationManagerSubmodule();

  virtual bool Initialize(std::map<int, std::shared_ptr<ISimulationManagerSubmodule>> subModules);
  virtual bool Terminate();

protected:
  SimulationManager* _pParentInstance;
  std::map<int, std::shared_ptr<ISimulationManagerSubmodule>> _subModules;

};

}