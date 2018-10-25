#include "TextureManager.h"

using namespace WeSp;

TextureManager::TextureManager(BaseModule &parentModule):
  BaseModule(parentModule),
  _defaultTexture(std::make_shared<Texture>("Resource/textures/plain.png"))
{
  // Instantiate submodules into map container
  //_subModules.insert(std::make_pair(ID_AI_MANAGER, std::make_shared<AIManager>(this)));
  //_subModules.insert(std::make_pair(ID_LOGIC_MANAGER, std::make_shared<LogicManager>(this)));

  // Load texture.
  _defaultTexture->LoadTextureA();

  DLog(eLogType::Success, "TextureManager instance created.");
}

TextureManager::~TextureManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "TextureManager instance destroyed.");
}

bool TextureManager::Initialize()
{
  // Initialize submodules.
  for (std::map<int, std::shared_ptr<BaseModule>>::iterator it = _subModules.begin(); it != _subModules.end(); ++it)
  {
    (*it).second->Initialize();

  #if RUN_ENGINE_API

    // Setup submodule pointer to EngineAPI.
    it->second->SetEngineApiPointer(_pEngineApi);

  #endif
  }

  // Class specific initialization

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "TextureManager instance initialized.");
  return true;
}

bool TextureManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "TextureManager instance terminated.");
  return true;
}

std::shared_ptr<Texture> TextureManager::GetDefaultTexture() const
{
  return _defaultTexture;
}