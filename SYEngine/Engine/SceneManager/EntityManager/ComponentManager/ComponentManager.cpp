
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
#include "Entity.h"

using namespace SYE; 

ComponentManager::ComponentManager(BaseModule& parentModule, EngineContext* pEngineContext):
  BaseModule(parentModule, pEngineContext)
{
  // Instantiate all submodules.
  _subModules.insert(std::make_pair(ID_MATERIAL_MANAGER, std::make_unique<MaterialManager>(*this, _pEngineContext)));
  _subModules.insert(std::make_pair(ID_MESH_MANAGER, std::make_unique<MeshManager>(*this, _pEngineContext)));
  _subModules.insert(std::make_pair(ID_MESH_GENERATOR, std::make_unique<MeshGenerator>(*this, _pEngineContext)));
  _subModules.insert(std::make_pair(ID_MODEL_MANAGER, std::make_unique<ModelManager>(*this, _pEngineContext)));
  _subModules.insert(std::make_pair(ID_SKYBOX_MANAGER, std::make_unique<SkyboxManager>(*this, _pEngineContext)));
  _subModules.insert(std::make_pair(ID_TEXTURE_MANAGER, std::make_unique<TextureManager>(*this, _pEngineContext)));

  // Enlist all submodules into EngineContext ptr table
  EnlistSubmodulesToEngineContext();

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

void ComponentManager::DestroyAllComponents()
{
  // Reset owner pointers of remaining Components to avoid accessing not valid pointer
  for (auto&& componentPair : _components)
  {
    componentPair.second->ResetOwnerPointers();
  }

  _components.clear();
}


// TODO: Delete this
std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& ComponentManager::GetPrimaryComponentSlotsRef(Entity* pEntity)
{
  return pEntity->GetPrimaryComponentSlotsRef();

}