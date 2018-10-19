#include "IInputManagerSubmodule.h"

using namespace WeSp;

IInputManagerSubmodule::IInputManagerSubmodule(InputManager* pParentInstance) :
  _pParentInstance(pParentInstance)
{}

IInputManagerSubmodule::~IInputManagerSubmodule() {}

bool IInputManagerSubmodule::Initialize(std::map<int, std::shared_ptr<IInputManagerSubmodule>> subModules)
{
  // If no modules send in
  if (subModules.size() <= 0)
  {
    DLog(eLogType::Error, "Empty InputManager submodule container send to initialize main module.")
    return false;
  }
  _subModules = subModules;
  return true;
}

bool IInputManagerSubmodule::Terminate()
{
  // Do all base terminating stuff
  return true;
}
