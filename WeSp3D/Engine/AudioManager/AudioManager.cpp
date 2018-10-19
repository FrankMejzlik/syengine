
#include "AudioManager.h"

AudioManager::AudioManager(Engine* pParentInstance):
  IMainEngineModule(pParentInstance)
{
  DLog(eLogType::Success, "AudioManager instance created.");
}

AudioManager::~AudioManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "AudioManager instance destroyed.");
}

bool AudioManager::Initialize(std::map<int, std::shared_ptr<IMainEngineModule>> modules)
{
  // Call parent Initialize method
  if (!IMainEngineModule::Initialize(modules))
  {
    DLog(eLogType::Error, "Initialization of base Initialize in AudioManager failed.");
    return false;
  }

  // Class specific initialization

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "AudioManager instance initialized.");
  return true;
}

bool AudioManager::Terminate()
{
  // Class specific terminate

  if (!IMainEngineModule::Terminate())
  {
    SetModuleState(eModuleState::Error);
    DLog(eLogType::Error, "Error terminating base of EntitiManager instance.");
    return false;
  }

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "AudioManager instance terminated.");
  return true;
}