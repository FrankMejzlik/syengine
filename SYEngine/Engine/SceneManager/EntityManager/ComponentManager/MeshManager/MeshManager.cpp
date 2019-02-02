#include "MeshManager.h"

using namespace SYE;


MeshManager::MeshManager(BaseModule &parentModule):
  BaseModule(parentModule)
{
  // Instantiate submodules into map container
  _subModules.insert(std::make_pair(ID_MESH_GENERATOR, std::make_unique<MeshGenerator>(*this)));

  DLog(eLogType::Success, "\t\t\t MeshManager instance created.");
}

MeshManager::~MeshManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "\t\t\t MeshManager instance destroyed.");
}

bool MeshManager::Initialize()
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
  DLog(eLogType::Success, "\t\t\t MeshManager instance initialized.");
  return true;
}

bool MeshManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "\t\t\t MeshManager instance terminated.");
  return true;
}

std::unique_ptr<Mesh> MeshManager::GenerateMeshQuad(dfloat width, dfloat height)
{
  std::unique_ptr<Mesh> newMesh = MESH_GENERATOR->GenerateMeshQuad(width, height, false);
  
  // TODO store Mesh

  return newMesh;
}

std::unique_ptr<Mesh> MeshManager::GenerateMeshBlock(dfloat width, dfloat height, dfloat length)
{
  std::unique_ptr<Mesh> newMesh = MESH_GENERATOR->GenerateMeshBlock(width, height, length, false);

  // TODO store Mesh

  return newMesh;
}