#include "TextureManager.h"

using namespace WeSp;

TextureManager::TextureManager(RenderingManager* pParentInstance):
  IRenderingManagerSubmodule(pParentInstance)
{
  DLog(eLogType::Success, "\t TextureManager instance created.");
}

TextureManager::~TextureManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "\t TextureManager instance destroyed.");
}

bool TextureManager::Initialize(std::map<int, std::shared_ptr<IRenderingManagerSubmodule>> modules)
{
  // Call parent Initialize method
  if (!IRenderingManagerSubmodule::Initialize(modules))
  {
    DLog(eLogType::Error, "\t Initialization of base Initialize in TextureManager failed.");
    return false;
  }

  // Class specific initialization

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "\t TextureManager instance initialized.");
  return true;
}

bool TextureManager::Terminate()
{
  // Class specific terminate

  if (!IRenderingManagerSubmodule::Terminate())
  {
    SetModuleState(eModuleState::Error);
    DLog(eLogType::Error, "\t Error terminating base of TextureManager instance.");
    return false;
  }

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "\t TextureManager instance terminated.");
  return true;
}