
#include "ComponentManager.h"

// Component submodules
#include "ControllerManager.h"
#include "MaterialManager.h"
#include "MeshManager.h"
#include "ModelManager.h"
#include "SkyboxManager.h"
#include "TextureManager.h"
#include "BlockCollider.h"

// Components
#include "Mesh.h"

using namespace SYE; 

ComponentManager::ComponentManager(BaseModule &parentModule):
  BaseModule(parentModule)
{
  // Instantiate all submodules.
  _subModules.insert(std::make_pair(ID_CONTROLLER_MANAGER, std::make_unique<ControllerManager>(*this)));
  _subModules.insert(std::make_pair(ID_MATERIAL_MANAGER, std::make_unique<MaterialManager>(*this)));
  _subModules.insert(std::make_pair(ID_MESH_MANAGER, std::make_unique<MeshManager>(*this)));
  _subModules.insert(std::make_pair(ID_MESH_GENERATOR, std::make_unique<MeshGenerator>(*this)));
  _subModules.insert(std::make_pair(ID_MODEL_MANAGER, std::make_unique<ModelManager>(*this)));
  _subModules.insert(std::make_pair(ID_SKYBOX_MANAGER, std::make_unique<SkyboxManager>(*this)));
  _subModules.insert(std::make_pair(ID_TEXTURE_MANAGER, std::make_unique<TextureManager>(*this)));

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
  for (std::map<int, std::unique_ptr<BaseModule>>::iterator it = _subModules.begin(); it != _subModules.end(); ++it)
  {
    (*it).second->Initialize();

  #if RUN_ENGINE_API

    // Setup submodule pointer to EngineAPI.
    it->second->SetEngineApiPointer(_pEngineApi);

  #endif
  }

  SetModuleState(eModuleState::OK);
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
