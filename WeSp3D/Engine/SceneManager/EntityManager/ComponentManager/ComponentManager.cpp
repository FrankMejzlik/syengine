#include "ComponentManager.h"

using namespace WeSp; 

ComponentManager::ComponentManager(BaseModule &parentModule):
  BaseModule(parentModule)
{
  _subModules.insert(std::make_pair(ID_CONTROLLER_MANAGER, std::make_shared<ControllerManager>(*this)));
  _subModules.insert(std::make_pair(ID_MATERIAL_MANAGER, std::make_shared<MaterialManager>(*this)));
  _subModules.insert(std::make_pair(ID_MESH_MANAGER, std::make_shared<MeshManager>(*this)));
  _subModules.insert(std::make_pair(ID_MODEL_MANAGER, std::make_shared<ModelManager>(*this)));
  _subModules.insert(std::make_pair(ID_SKYBOX_MANAGER, std::make_shared<SkyboxManager>(*this)));
  _subModules.insert(std::make_pair(ID_TEXTURE_MANAGER, std::make_shared<TextureManager>(*this)));


  DLog(eLogType::Success, "\t\tComponentManager instance created.");
}


ComponentManager::~ComponentManager()
{
  DLog(eLogType::Success, "\t\tComponentManager instance destroyed.");
}

bool ComponentManager::Initialize()
{

  // Class specific initialization

  // Initialize submodules.
  for (std::map<int, std::shared_ptr<BaseModule>>::iterator it = _subModules.begin(); it != _subModules.end(); ++it)
  {
    (*it).second->Initialize();

  #if RUN_ENGINE_API

    // Setup submodule pointer to EngineAPI.
    it->second->SetEngineApiPointer(_pEngineApi);

  #endif
  }

  SetModuleState(eModuleState::Idle);
  DLog(eLogType::Success, "ComponentManager instance initialized.");
  return true;
}

bool ComponentManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "ComponentManager instance terminated.");
  return true;
}