
#include "ComponentManager.h"

using namespace SYE; 

ComponentManager::ComponentManager(BaseModule &parentModule):
  BaseModule(parentModule)
{
  // Instantiate all submodules.
  _subModules.insert(std::make_pair(ID_CONTROLLER_MANAGER, std::make_shared<ControllerManager>(*this)));
  _subModules.insert(std::make_pair(ID_MATERIAL_MANAGER, std::make_shared<MaterialManager>(*this)));
  _subModules.insert(std::make_pair(ID_MESH_MANAGER, std::make_shared<MeshManager>(*this)));
  _subModules.insert(std::make_pair(ID_MODEL_MANAGER, std::make_shared<ModelManager>(*this)));
  _subModules.insert(std::make_pair(ID_SKYBOX_MANAGER, std::make_shared<SkyboxManager>(*this)));
  _subModules.insert(std::make_pair(ID_TEXTURE_MANAGER, std::make_shared<TextureManager>(*this)));


  _pTextureManager = TEXTURE_MANAGER;

  DLog(eLogType::Success, "\t\tComponentManager instance created.");
}

ComponentManager::~ComponentManager()
{
  DLog(eLogType::Success, "\t\tComponentManager instance destroyed.");
}

std::shared_ptr<Collider> ComponentManager::CreateBoxCollider(
  std::shared_ptr<Entity> pEntity,
  glm::vec3 position, glm::vec3 rotation, glm::vec3 scale,
  dfloat width,  dfloat heigt,  dfloat length,
  bool bIsStatic
)
{
  return std::make_shared<BlockCollider>(
    pEntity, 
    position, rotation, scale, 
    width, heigt, length,
    bIsStatic, true
    );
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

std::shared_ptr<Mesh> ComponentManager::GenerateMeshQuad(dfloat width, dfloat height)
{
  std::shared_ptr<Mesh> newComponent = MESH_MANAGER->GenerateMeshQuad(width, height);

  return newComponent;

}

std::shared_ptr<Mesh> ComponentManager::GenerateMeshBlock(dfloat width, dfloat height, dfloat length)
{
  std::shared_ptr<Mesh> newComponent = MESH_MANAGER->GenerateMeshBlock(width, height,length);

  return newComponent;
}


std::shared_ptr<Model> ComponentManager::CreateModel(std::shared_ptr<Entity> pEntity, std::shared_ptr<Mesh> pQuadMesh, std::shared_ptr<Texture> pTexture, std::shared_ptr<Shininess> pShininess)
{
  std::shared_ptr<Model> newComponent = MODEL_MANAGER->CreateModel(pEntity, pQuadMesh, pTexture, pShininess);
  return newComponent;
}

std::shared_ptr<Model> ComponentManager::CreateModelFromFile(
  std::shared_ptr<Entity> pEntity,
  std::string filePath
)
{
  std::shared_ptr<Model> newComponent = MODEL_MANAGER->CreateModelFromFile(pEntity, filePath);
  return newComponent;
}