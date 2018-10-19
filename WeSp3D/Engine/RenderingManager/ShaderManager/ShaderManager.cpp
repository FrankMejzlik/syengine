#include "ShaderManager.h"

using namespace WeSp;

ShaderManager::ShaderManager(RenderingManager* pParentInstance):
  IRenderingManagerSubmodule(pParentInstance)
{
  DLog(eLogType::Success, "\t ShaderManager instance created.");
}

ShaderManager::~ShaderManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "\t ShaderManager instance destroyed.");
}

bool ShaderManager::Initialize(std::map<int, std::shared_ptr<IRenderingManagerSubmodule>> modules)
{
  // Call parent Initialize method
  if (!IRenderingManagerSubmodule::Initialize(modules))
  {
    DLog(eLogType::Error, "\t Initialization of base Initialize in ShaderManager failed.");
    return false;
  }

  // Class specific initialization

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "\t ShaderManager instance initialized.");
  return true;
}

bool ShaderManager::Terminate()
{
  // Class specific terminate

  if (!IRenderingManagerSubmodule::Terminate())
  {
    SetModuleState(eModuleState::Error);
    DLog(eLogType::Error, "\t Error terminating base of ShaderManager instance.");
    return false;
  }

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "\t ShaderManager instance terminated.");
  return true;
}