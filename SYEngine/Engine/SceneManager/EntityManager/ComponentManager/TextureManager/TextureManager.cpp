#include "TextureManager.h"

using namespace SYE;

TextureManager::TextureManager(BaseModule &parentModule):
  BaseModule(parentModule)
{
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


  SetModuleState(eModuleState::OK);
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

std::unique_ptr<Texture> TextureManager::CreateDefaultTexture()
{
  std::unique_ptr<Texture> _defaultTexture = std::make_unique<Texture>(nullptr, _subModules, _fake, CONCATENATE_DEFINES(PATH_TEXTURES, FILENAME_DEFAULT_TEXTURE));
  _defaultTexture->LoadTexture();

  return _defaultTexture;
}