
#include "ComponentManager.h"

using namespace SYE; 

ComponentManager::ComponentManager(BaseModule &parentModule):
  BaseModule(parentModule)
{
  // Instantiate all submodules.
  _subModules.insert(std::make_pair(ID_CONTROLLER_MANAGER, std::make_unique<ControllerManager>(*this)));
  _subModules.insert(std::make_pair(ID_MATERIAL_MANAGER, std::make_unique<MaterialManager>(*this)));
  _subModules.insert(std::make_pair(ID_MESH_MANAGER, std::make_unique<MeshManager>(*this)));
  _subModules.insert(std::make_pair(ID_MODEL_MANAGER, std::make_unique<ModelManager>(*this)));
  _subModules.insert(std::make_pair(ID_SKYBOX_MANAGER, std::make_unique<SkyboxManager>(*this)));
  _subModules.insert(std::make_pair(ID_TEXTURE_MANAGER, std::make_unique<TextureManager>(*this)));


  _pTextureManager = TEXTURE_MANAGER;

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

std::unique_ptr<Mesh> ComponentManager::GenerateMeshQuad(dfloat width, dfloat height)
{
  std::unique_ptr<Mesh> newComponent = MESH_MANAGER->GenerateMeshQuad(width, height);

  return newComponent;

}

std::unique_ptr<Mesh> ComponentManager::GenerateMeshBlock(dfloat width, dfloat height, dfloat length)
{
  std::unique_ptr<Mesh> newComponent = MESH_MANAGER->GenerateMeshBlock(width, height,length);

  return newComponent;
}

Component* ComponentManager::InsertComponent(std::unique_ptr<Component>&& pNewComponent)
{
  auto result = _components.insert(std::make_pair(pNewComponent->GetGuid(), std::move(pNewComponent)));

  return result.first->second.get();
}

Component* ComponentManager::CreateBoxCollider(
  Entity* pEntity,
  glm::vec3 position, glm::vec3 rotation, glm::vec3 scale,
  dfloat width, dfloat heigt, dfloat length,
  bool bIsStatic
)
{
  return InsertComponent(std::make_unique<BlockCollider>(
    pEntity,
    position, rotation, scale,
    width, heigt, length,
    bIsStatic, true
    ));
}


Component* ComponentManager::CreateModel(Entity* pEntity, std::unique_ptr<Mesh>&& pQuadMesh, std::unique_ptr<Texture>&& pTexture, std::unique_ptr<Shininess>&& pShininess)
{
  std::unique_ptr<Component> newComponent = MODEL_MANAGER->CreateModel(pEntity, std::move(pQuadMesh), std::move(pTexture), std::move(pShininess));
  return InsertComponent(std::move(newComponent));
}

Component* ComponentManager::CreateModelFromFile(
  Entity* pEntity,
  std::string_view filePath
)
{
  std::unique_ptr<Component> newComponent = MODEL_MANAGER->CreateModelFromFile(pEntity, filePath);
  return InsertComponent(std::move(newComponent));
}