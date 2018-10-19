#include "ISimulationManagerSubmodule.h"

using namespace WeSp;

ISimulationManagerSubmodule::ISimulationManagerSubmodule(SimulationManager* pParentInstance) :
  _pParentInstance(pParentInstance)
{}

ISimulationManagerSubmodule::~ISimulationManagerSubmodule() {}

bool ISimulationManagerSubmodule::Initialize(std::map<int, std::shared_ptr<ISimulationManagerSubmodule>> subModules)
{
  // If no modules send in
  if (subModules.size() <= 0)
  {
    DLog(eLogType::Error, "Empty SimulationManager submodule container send to initialize main module.")
    return false;
  }
  _subModules = subModules;
  return true;
}

bool ISimulationManagerSubmodule::Terminate()
{
  // Do all base terminating stuff
  return true;
}
