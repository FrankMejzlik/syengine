#include "SkyboxManager.h"

using namespace WeSp;

SkyboxManager::SkyboxManager(RenderingManager* pParentInstance):
  IRenderingManagerSubmodule(pParentInstance)
{
  DLog(eLogType::Success, "\t SkyboxManager instance created.");
}

SkyboxManager::~SkyboxManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "\t SkyboxManager instance destroyed.");
}

bool SkyboxManager::Initialize(std::map<int, std::shared_ptr<IRenderingManagerSubmodule>> modules)
{
  // Call parent Initialize method
  if (!IRenderingManagerSubmodule::Initialize(modules))
  {
    DLog(eLogType::Error, "\t Initialization of base Initialize in SkyboxManager failed.");
    return false;
  }

  // Class specific initialization

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "\t SkyboxManager instance initialized.");
  return true;
}

bool SkyboxManager::Terminate()
{
  // Class specific terminate

  if (!IRenderingManagerSubmodule::Terminate())
  {
    SetModuleState(eModuleState::Error);
    DLog(eLogType::Error, "\t Error terminating base of SkyboxManager instance.");
    return false;
  }

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "\t SkyboxManager instance terminated.");
  return true;
}