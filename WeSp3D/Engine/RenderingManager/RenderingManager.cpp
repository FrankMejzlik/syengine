#include "RenderingManager.h"

RenderingManager::RenderingManager(Engine* pParentInstance):
  IMainEngineModule(pParentInstance)
{

  // Instantiate submodules into map container
  _subModules.insert(std::make_pair(ID_ANIMATION_MANAGER, std::make_shared<AnimationManager>(this)));
  _subModules.insert(std::make_pair(ID_MATERIAL_MANAGER, std::make_shared<MaterialManager>(this)));
  _subModules.insert(std::make_pair(ID_MESH_MANAGER, std::make_shared<MeshManager>(this)));
  _subModules.insert(std::make_pair(ID_SHADER_MANAGER, std::make_shared<ShaderManager>(this)));
  _subModules.insert(std::make_pair(ID_SHADOW_MANAGER, std::make_shared<ShadowManager>(this)));
  _subModules.insert(std::make_pair(ID_SKYBOX_MANAGER, std::make_shared<SkyboxManager>(this)));
  _subModules.insert(std::make_pair(ID_TEXTURE_MANAGER, std::make_shared<TextureManager>(this)));
  _subModules.insert(std::make_pair(ID_WINDOW_MANAGER, std::make_shared<WindowManager>(this)));

  DLog(eLogType::Success, "RenderingManager instance created.");
}

RenderingManager::~RenderingManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "RenderingManager instance destroyed.");
}

bool RenderingManager::Initialize(std::map<int, std::shared_ptr<IMainEngineModule>> modules)
{
  // Call parent Initialize method
  if (!IMainEngineModule::Initialize(modules))
  {
    DLog(eLogType::Error, "Initialization of base Initialize in RenderingManager failed.");
    return false;
  }

  // Class specific initialization
  // -- Goes here
  // Class specific initialization

  // Initialize submodules
  for (std::map<int, std::shared_ptr<IRenderingManagerSubmodule>>::iterator it = _subModules.begin(); it != _subModules.end(); ++it)
  {
    (*it).second->Initialize(_subModules);
  }

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "RenderingManager instance initialized.");
  return true;
}

bool RenderingManager::Terminate()
{
  // Class specific terminate

  if (!IMainEngineModule::Terminate())
  {
    SetModuleState(eModuleState::Error);
    DLog(eLogType::Error, "Error terminating base of EntitiManager instance.");
    return false;
  }

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "RenderingManager instance terminated.");
  return true;
}