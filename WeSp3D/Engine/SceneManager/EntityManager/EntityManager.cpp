#include "EntityManager.h"

using namespace WeSp;

EntityManager::EntityManager(BaseModule &parentModule):
  BaseModule(parentModule)
{
  _subModules.insert(std::make_pair(ID_COMPONENT_MANAGER, std::make_shared<ComponentManager>(*this)));

  DLog(eLogType::Success, "\t EntityManager instance created.");
}

EntityManager::~EntityManager()
{
  // If instance not terminated, do so
  if (GetModuleState() != eModuleState::Null)
  {
    Terminate();
  }

  DLog(eLogType::Success, "\t EntityManager instance destroyed.");
}

bool EntityManager::Initialize()
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
  DLog(eLogType::Success, "\t EntityManager instance initialized.");
  return true;
}

bool EntityManager::Terminate()
{
  // Class specific terminate

  SetModuleState(eModuleState::Null);
  DLog(eLogType::Success, "\t EntityManager instance terminated.");
  return true;
}

std::shared_ptr<Quad> EntityManager::CreateQuad(
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  dfloat width, dfloat height
)
{
  return nullptr;
}
