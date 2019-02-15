#include "EntityManager.h"

using namespace SYE;

EntityManager::EntityManager(BaseModule &parentModule):
  BaseModule(parentModule)
{
  _subModules.insert(std::make_pair(ID_COMPONENT_MANAGER, std::make_unique<ComponentManager>(*this)));

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
  for (std::map<int, std::unique_ptr<BaseModule>>::iterator it = _subModules.begin(); it != _subModules.end(); ++it)
  {
    (*it).second->Initialize();

  #if RUN_ENGINE_API

    // Setup submodule pointer to EngineAPI.
    it->second->SetEngineApiPointer(_pEngineApi);

  #endif
  }

  SetModuleState(eModuleState::OK);
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

Entity* EntityManager::CreateEntity()
{
  // Instantiate new Entity
  std::unique_ptr<Entity> newEntity = std::make_unique<Entity>(COMPONENT_MANAGER);

  return InsertEntity(std::move(newEntity));
}



Entity* EntityManager::InsertEntity(std::unique_ptr<Entity>&& pNewEntity)
{
  auto result = _entityList.insert(std::make_pair(pNewEntity->GetGuid(), std::move(pNewEntity)));

  return result.first->second.get();
}

// vvv obsolate

Entity* EntityManager::CreateCamera(
  std::string_view cameraName, 
  glm::vec3 positionVector, 
  glm::vec3 startUpDirection, 
  float startYaw, float startPitch, 
  float turnSpeed, float moveSpeed
)
{
  // Instantiate new Quad instance.
  std::unique_ptr<_Camera> newEntity = std::make_unique<_Camera>(
    COMPONENT_MANAGER,
    positionVector, startUpDirection, startYaw, startPitch,
    turnSpeed, moveSpeed
    );

  // Set name of Entity.
  newEntity->SetEntityName(cameraName);


  return InsertEntity(std::move(newEntity));
}



Entity* EntityManager::CreateQuad(
  std::string_view entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  dfloat width, dfloat height
)
{
  // Instantiate new Quad instance.
  std::unique_ptr<Quad> newEntity = std::make_unique<Quad>(
    COMPONENT_MANAGER, 
    positionVector, rotationVector, scaleVector,
    true, // Is static.
    width, height
  );
  // Set name of Entity.
  newEntity->SetEntityName(entityName);


  return InsertEntity(std::move(newEntity));
}

Entity* EntityManager::CreateBlock(
  std::string_view entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  dfloat width, dfloat height, dfloat length,
  bool bIsStatic
)
{
  // Instantiate new Block instance.
  std::unique_ptr<Block> newEntity = std::make_unique<Block>(
    COMPONENT_MANAGER, 
    positionVector, rotationVector, scaleVector,
    true, // Is non-animated.
    width, height, length
    );

  // Set name of Entity.
  newEntity->SetEntityName(entityName);

  // Create new Box Collider.
  Collider* newCollider = (Collider*)COMPONENT_MANAGER->CreateBoxCollider(
    newEntity.get(), 
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    width, height, length,
    bIsStatic
  );
  newEntity->AddCollider(newCollider);

  return InsertEntity(std::move(newEntity));
}

Entity* EntityManager::CreateStaticModelFromFile(
  std::string_view entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  std::string_view filePath
)
{
  // Instantiate new Block instance.
  std::unique_ptr<WorldObject> newEntity = std::make_unique<WorldObject>(
    COMPONENT_MANAGER, 
    positionVector, rotationVector, scaleVector,
    true, // Is static.
    filePath
    );
  // Set name of Entity.
  newEntity->SetEntityName(entityName);

  return InsertEntity(std::move(newEntity));
}

Entity* EntityManager::CreateDirectionalLight(
  std::string_view entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  glm::vec3 lightColour, glm::vec3 lightIntensities,
  glm::vec3 shadowMapSize,
  glm::vec3 lightDirection
)
{
  std::unique_ptr<DirectionalLight> newEntity = std::make_unique<DirectionalLight>(
    COMPONENT_MANAGER,
    positionVector, rotationVector, scaleVector,
    lightColour, lightIntensities,
    shadowMapSize, lightDirection
    );

  // Set name of Entity.
  newEntity->SetEntityName(entityName);

  return InsertEntity(std::move(newEntity));
}

Entity* EntityManager::CreatePointLight(
  std::string_view entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  glm::vec3 lightColour,
  glm::vec3 lightIntensities,
  glm::vec3 shadowMapSize,
  glm::vec2 planeDimensions,
  glm::vec3 coefficients
)
{
  std::unique_ptr<PointLight> newEntity = std::make_unique<PointLight>(
    COMPONENT_MANAGER,
    positionVector, rotationVector, scaleVector,
    lightColour, lightIntensities,
    shadowMapSize, planeDimensions, coefficients
    );

  // Set name of Entity.
  newEntity->SetEntityName(entityName);

  return InsertEntity(std::move(newEntity));
}

Entity* EntityManager::CreateSpotLight(
  std::string_view entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  glm::vec3 lightColour,
  glm::vec3 lightIntensities,
  glm::vec3 shadowMapSize,
  glm::vec2 planeDimensions,
  glm::vec3 coefficients,
  glm::vec3 lightDirection,
  dfloat coneAngle
)
{
  std::unique_ptr<SpotLight> newEntity = std::make_unique<SpotLight>(
    COMPONENT_MANAGER,
    positionVector, rotationVector, scaleVector,
    lightColour, lightIntensities,
    shadowMapSize, planeDimensions, coefficients,
    lightDirection, coneAngle
    );

  // Set name of Entity.
  newEntity->SetEntityName(entityName);

  return InsertEntity(std::move(newEntity));
}
