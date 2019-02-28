
#include "AudioManager.h"

AudioManager::AudioManager(BaseModule& parentModule, EngineContext* pEngineContext):
  BaseModule(parentModule, pEngineContext)
{
  // Enlist all submodules into EngineContext ptr table
  EnlistSubmodulesToEngineContext();

  DLog(eLogType::Success, "\t AudioManager instance created.");
}

AudioManager::~AudioManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "\t AudioManager instance destroyed.");
}

bool AudioManager::Initialize()
{

  SetModuleState(eModuleState::OK);
  DLog(eLogType::Success, "\t AudioManager instance initialized.");
  return true;
}

bool AudioManager::Terminate()
{
  // Class specific terminate


  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "\t AudioManager instance terminated.");
  return true;
}