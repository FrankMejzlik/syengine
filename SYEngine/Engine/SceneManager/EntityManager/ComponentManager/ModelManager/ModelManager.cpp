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

std::unique_ptr<Model> ModelManager::CreateModel(Entity* pEntity, std::unique_ptr<Mesh>&& pQuadMesh, std::unique_ptr<Texture>&& pTexture, std::unique_ptr<_Shininess>&& pShininess)
{
  std::unique_ptr<Model> newModel = std::make_unique<Model>(pEntity, _subModules, _fake);

  // Add Mesh, Texture and Shininess to model
  size_t meshIndex = newModel->AddMesh(std::move(pQuadMesh));
  size_t textureIndex = 0;
  size_t shininessIndex = 0;

  // If texture provided.
  if (pTexture)
  {
    textureIndex = newModel->AddTexture(std::move(pTexture));
  }
  newModel->SetMeshIndexToShininess(meshIndex, shininessIndex);

  // If shininess provided.
  if (pShininess)
  {
    shininessIndex = newModel->AddShininess(std::move(pShininess));
  }
  newModel->SetMeshIndexToShininess(meshIndex, shininessIndex);

  
  return newModel;
}


std::unique_ptr<Model> ModelManager::CreateModelFromFile(Entity* pEntity, std::string_view filePath)
{
  std::unique_ptr<Model> pNewModel = std::make_unique<Model>(pEntity, _subModules, _fake);

  pNewModel->LoadModelFromFile(filePath);

  return pNewModel;
}
