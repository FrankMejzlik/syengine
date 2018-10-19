#include "MeshManager.h"

using namespace WeSp;

MeshManager::MeshManager(RenderingManager* pParentInstance):
  IRenderingManagerSubmodule(pParentInstance)
{
  DLog(eLogType::Success, "\t MeshManager instance created.");
}

MeshManager::~MeshManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "\t MeshManager instance destroyed.");
}

bool MeshManager::Initialize(std::map<int, std::shared_ptr<IRenderingManagerSubmodule>> modules)
{
  // Call parent Initialize method
  if (!IRenderingManagerSubmodule::Initialize(modules))
  {
    DLog(eLogType::Error, "\t Initialization of base Initialize in MeshManager failed.");
    return false;
  }

  // Class specific initialization

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "\t MeshManager instance initialized.");
  return true;
}

bool MeshManager::Terminate()
{
  // Class specific terminate

  if (!IRenderingManagerSubmodule::Terminate())
  {
    SetModuleState(eModuleState::Error);
    DLog(eLogType::Error, "\t Error terminating base of MeshManager instance.");
    return false;
  }

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "\t MeshManager instance terminated.");
  return true;
}