
#include "AudioManager.h"

AudioManager::AudioManager(BaseModule &parentModule):
  BaseModule(parentModule)
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

bool AudioManager::Initialize()
{

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "AudioManager instance initialized.");
  return true;
}

bool AudioManager::Terminate()
{
  // Class specific terminate


  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "AudioManager instance terminated.");
  return true;
}