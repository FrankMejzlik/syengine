
#include "AnimationManager.h"

using namespace WeSp;

AnimationManager::AnimationManager(RenderingManager* pParentInstance):
  IRenderingManagerSubmodule(pParentInstance)
{
  DLog(eLogType::Success, "\t AnimationManager instance created.");
}

AnimationManager::~AnimationManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "\t AnimationManager instance destroyed.");
}

bool AnimationManager::Initialize(std::map<int, std::shared_ptr<IRenderingManagerSubmodule>> modules)
{
  // Call parent Initialize method
  if (!IRenderingManagerSubmodule::Initialize(modules))
  {
    DLog(eLogType::Error, "\t Initialization of base Initialize in AnimationManager failed.");
    return false;
  }

  // Class specific initialization

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "\t AnimationManager instance initialized.");
  return true;
}

bool AnimationManager::Terminate()
{
  // Class specific terminate

  if (!IRenderingManagerSubmodule::Terminate())
  {
    SetModuleState(eModuleState::Error);
    DLog(eLogType::Error, "\t Error terminating base of AnimationManager instance.");
    return false;
  }

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "\t AnimationManager instance terminated.");
  return true;
}