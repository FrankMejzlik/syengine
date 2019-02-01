#include "TextureManager.h"

using namespace SYE;

TextureManager::TextureManager(BaseModule &parentModule):
  BaseModule(parentModule)
{
  // Instantiate submodules into map container
  //_subModules.insert(std::make_pair(ID_AI_MANAGER, std::make_unique<AIManager>(this)));
  //_subModules.insert(std::make_pair(ID_LOGIC_MANAGER, std::make_unique<LogicManager>(this)));

  // Load texture.
  //_defaultTexture->LoadTextureA();

  DLog(eLogType::Success, "\t\t\tTextureManager instance created.");
}

TextureManager::~TextureManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "\t\t\tTextureManager instance destroyed.");
}

bool TextureManager::Initialize()
{
  // Initialize submodules.
  for (std::map<int, std::unique_ptr<BaseModule>>::iterator it = _subModules.begin(); it != _subModules.end(); ++it)
  {
    (*it).second->Initialize();

  #if RUN_ENGINE_API

    // Setup submodule pointer to EngineAPI.
    it->second->SetEngineApiPointer(_pEngineApi);

  #endif
  }

  // Class specific initialization


  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "\t\t\tTextureManager instance initialized.");
  return true;
}

bool TextureManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "\t\t\tTextureManager instance terminated.");
  return true;
}

std::unique_ptr<Texture> TextureManager::GetDefaultTexture() const
{
  std::unique_ptr<Texture> _defaultTexture = std::make_unique<Texture>(nullptr, CONCATENATE_DEFINES(PATH_TEXTURES, FILENAME_DEFAULT_TEXTURE));
  _defaultTexture->LoadTexture();

  return _defaultTexture;
}