#include "ModelManager.h"

using namespace SYE;


ModelManager::ModelManager(BaseModule &parentModule):
  BaseModule(parentModule)
{
  DLog(eLogType::Success, "\t\t\t ModelManager instance created.");
}

ModelManager::~ModelManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "\t\t\t ModelManager instance destroyed.");
}

bool ModelManager::Initialize()
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
  DLog(eLogType::Success, "\t\t\t ModelManager instance initialized.");
  return true;
}

bool ModelManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "\t\t\t ModelManager instance terminated.");
  return true;
}

std::shared_ptr<Model> ModelManager::CreateModel(std::shared_ptr<Entity> pEntity, std::shared_ptr<Mesh> pQuadMesh, std::shared_ptr<Texture> pTexture, std::shared_ptr<Shininess> pShininess)
{
  std::shared_ptr<Model> newModel = std::make_shared<Model>(pEntity);

  // Add Mesh, Texture and Shininess to model
  size_t meshIndex = newModel->AddMesh(pQuadMesh);
  size_t textureIndex = 0;
  size_t shininessIndex = 0;

  // If texture provided.
  if (pTexture)
  {
    textureIndex = newModel->AddTexture(pTexture);
  }
  newModel->SetMeshIndexToShininess(meshIndex, shininessIndex);

  // If shininess provided.
  if (pShininess)
  {
    shininessIndex = newModel->AddShininess(pShininess);
  }
  newModel->SetMeshIndexToShininess(meshIndex, shininessIndex);

  
  return newModel;
}


std::shared_ptr<Model> ModelManager::CreateModelFromFile(std::shared_ptr<Entity> pEntity, std::string filePath)
{
  std::shared_ptr<Model> pNewModel = std::make_shared<Model>(pEntity);

  pNewModel->LoadModelFromFile(filePath);

  return pNewModel;
}
