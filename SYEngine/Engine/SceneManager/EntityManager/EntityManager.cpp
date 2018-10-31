#include "EntityManager.h"

using namespace SYE;

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
  std::string entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  dfloat width, dfloat height
)
{
  // Instantiate new Quad instance.
  std::shared_ptr<Quad> newEntity = std::make_shared<Quad>(
    COMPONENT_MANAGER, 
    positionVector, rotationVector, scaleVector,
    true, // Is static.
    width, height
  );
  // Set name of Entity.
  newEntity->SetEntityName(entityName);


  return newEntity;
}

std::shared_ptr<Block> EntityManager::CreateBlock(
  std::string entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  dfloat width, dfloat height, dfloat length
)
{
  // Instantiate new Block instance.
  std::shared_ptr<Block> newEntity = std::make_shared<Block>(
    COMPONENT_MANAGER, 
    positionVector, rotationVector, scaleVector,
    true, // Is static.
    width, height, length
    );
  // Set name of Entity.
  newEntity->SetEntityName(entityName);

  // Create new Box Collider.
  std::shared_ptr<Collider> newCollider = COMPONENT_MANAGER->CreateBoxCollider(
    newEntity, 
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    width, height, length
  );
  newEntity->AddCollider(newCollider);

  return newEntity;
}

std::shared_ptr<WorldObject> EntityManager::CreateStaticModelFromFile(
  std::string entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  std::string filePath
)
{
  // Instantiate new Block instance.
  std::shared_ptr<WorldObject> newEntity = std::make_shared<WorldObject>(
    COMPONENT_MANAGER, 
    positionVector, rotationVector, scaleVector,
    true, // Is static.
    filePath
    );
  // Set name of Entity.
  newEntity->SetEntityName(entityName);

  return newEntity;
}
