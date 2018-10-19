#include "IRenderingManagerSubmodule.h"

using namespace WeSp;

IRenderingManagerSubmodule::IRenderingManagerSubmodule(RenderingManager* pParentInstance) :
  _pParentInstance(pParentInstance)
{}

IRenderingManagerSubmodule::~IRenderingManagerSubmodule() {}

bool IRenderingManagerSubmodule::Initialize(std::map<int, std::shared_ptr<IRenderingManagerSubmodule>> subModules)
{
  // If no modules send in
  if (subModules.size() <= 0)
  {
    DLog(eLogType::Error, "Empty RenderingManager submodule container send to initialize main module.")
    return false;
  }
  _subModules = subModules;
  return true;
}

bool IRenderingManagerSubmodule::Terminate()
{
  // Do all base terminating stuff
  return true;
}
