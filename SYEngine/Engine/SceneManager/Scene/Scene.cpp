
#include "Scene.h"

#include "Transform.h"
#include "MeshRenderer.h"
#include "Rigidbody.h"
#include "BlockCollider.h"
#include "Texture.h"
#include "Material_.h"
#include "DirectionalLight_.h"
#include "PointLight_.h"
#include "SpotLight_.h"

using namespace SYE;

Scene::Scene(EntityManager* pEntityManager, std::string_view sceneName) noexcept :
  _pEntityManager(pEntityManager),
  _sceneContext(sceneName),
  _pEditorCamera(nullptr)
{
  DLog(eLogType::Success, "Scene with name %s instantiated.", _sceneContext.m_sceneName.data());
}

Scene::~Scene() noexcept
{
  DLog(eLogType::Success, "Scene with name %s destroyed.", _sceneContext.m_sceneName.data());
}

_Camera* Scene::GetEditorCamera() const
{
  return _pEditorCamera;
}


std::string_view Scene::GetSceneName() const
{
  return _sceneContext.m_sceneName;
}

size_t Scene::GetSceneNumberOfEntities() const
{
  return _entities.size();
}

Entity* Scene::InsertEntity(Entity* pEntityToInsert)
{
  _entities.insert(std::make_pair(pEntityToInsert->GetGuid(), pEntityToInsert));

  // If has Colliders, insert them into map as well.
  if (pEntityToInsert->GetBHasColliders())
  {
    InsertActiveColliders(pEntityToInsert);
  }

  return pEntityToInsert;
}

bool Scene::DeleteEntity(Entity* pEntityToDelete)
{
  // If has Colliders, delete them.
  if (pEntityToDelete->GetBHasColliders())
  {
    DeleteActiveColliders(pEntityToDelete);
  }

  // Delete it from hash map.
  _entities.erase(pEntityToDelete->GetGuid());

  return true;
}

Entity* Scene::CreateQuad(
  Vector3f positionVector, Vector3f rotationVector, Vector3f scaleVector,
  dfloat width, dfloat height,
  bool isStatic
)
{ 

  UNREFERENCED_PARAMETER(positionVector);
  UNREFERENCED_PARAMETER(rotationVector);
  UNREFERENCED_PARAMETER(scaleVector);
  UNREFERENCED_PARAMETER(height);
  UNREFERENCED_PARAMETER(width);
  UNREFERENCED_PARAMETER(isStatic);

  // Call EntityManager to create new Quad Entity.
  Entity* pNewEntity = _pEntityManager->CreateEntity(this);

  // Add Transform Component
  Transform* pTransform = pNewEntity->AddComponent<Transform>();
  pTransform->SetPosition(positionVector);
  pTransform->SetRotation(rotationVector);
  pTransform->SetScale(scaleVector);

  // Add MeshRenderer Component
  MeshRenderer* pMeshRenderer = pNewEntity->AddComponent<MeshRenderer>();
  {
    Mesh* pMesh = pMeshRenderer->AddMesh();
    {
      pMesh->ClearMesh();
      pMesh->MakeQuad(width, height);
    }
    Material* pMaterial = pMeshRenderer->AddMaterial();
    pMaterial;

    pMeshRenderer->AddMeshToMaterialIndex(0ULL, 0ULL);
  }

  return InsertEntity_(pNewEntity);
}


Entity* Scene::CreateBlock(
  Vector3f positionVector, Vector3f rotationVector, Vector3f scaleVector,
  dfloat width, dfloat height, dfloat length,
  bool isStatic
)
{ 

  UNREFERENCED_PARAMETER(positionVector);
  UNREFERENCED_PARAMETER(rotationVector);
  UNREFERENCED_PARAMETER(scaleVector);
  UNREFERENCED_PARAMETER(height);
  UNREFERENCED_PARAMETER(width);
  UNREFERENCED_PARAMETER(length);
  UNREFERENCED_PARAMETER(isStatic);

  // Call EntityManager to create new Quad Entity.
  Entity* pNewEntity = _pEntityManager->CreateEntity(this);
  
  // Add Transform Component
  Transform* pTransform = pNewEntity->AddComponent<Transform>();
  pTransform->SetPosition(positionVector);
  pTransform->SetRotation(rotationVector);
  pTransform->SetScale(scaleVector);

  // Add MeshRenderer Component
  MeshRenderer* pMeshRenderer = pNewEntity->AddComponent<MeshRenderer>();
  {
    Mesh* pMesh = pMeshRenderer->AddMesh();
    {
      pMesh->ClearMesh();
      pMesh->MakeBlock(width, height, length);
    }
    Material* pMaterial = pMeshRenderer->AddMaterial();
    pMaterial;

    pMeshRenderer->AddMeshToMaterialIndex(0ULL, 0ULL);
  }
 
  // Add BlockCollider Component
  BlockCollider* pBlockCollider = pNewEntity->AddComponent<BlockCollider>();
  pBlockCollider;

  // Add Rigigbody Component
  Rigidbody* pRigidBody = pNewEntity->AddComponent<Rigidbody>();
  pRigidBody;

  return InsertEntity_(pNewEntity);
}


Entity* Scene::CreateDirectionalLight(
  Vector3f positionVector, Vector3f rotationVector, Vector3f scaleVector,
  Vector3f colour, Vector3f intensities, Vector3u shadowDimensions,
  Vector3f direction,
  bool isStatic
)
{
  UNREFERENCED_PARAMETER(isStatic);

  // Create new Entity
  Entity* pNewEntity = _pEntityManager->CreateEntity(this);

  // Add Transform Component
  Transform* pTransform = pNewEntity->AddComponent<Transform>();
  pTransform->SetPosition(positionVector);
  pTransform->SetRotation(rotationVector);
  pTransform->SetScale(scaleVector);

  // Add DirectionalLight Component
  DirectionalLight* pLight = pNewEntity->AddComponent<DirectionalLight>();
  pLight->SetColour(colour.GetData());
  pLight->SetInensities(intensities.GetData());
  pLight->SetShadowDimensions(shadowDimensions.GetData());
  pLight->SetLightDirection(direction.GetData());

  
  return InsertEntity_(pNewEntity);
}

size_t Scene::MapTypeToSlot(size_t type)
{
  // Choose where to put this specific type
  switch (static_cast<Component::eType>(type))
  {
  case Component::eType::TRANSFORM:
    return COMPONENT_TRANSFORM_SLOT;
    break;

  case Component::eType::DIRECTIONAL_LIGHT:
    return COMPONENT_DIRECTIONAL_LIGHT_SOURCE_SLOT;
    break;

  case Component::eType::POINT_LIGHT:
    return COMPONENT_POINT_LIGHT_SOURCE_SLOT;
    break;

  case Component::eType::SPOT_LIGHT:
    return COMPONENT_SPOT_LIGHT_SOURCE_SLOT;
    break;

  case Component::eType::SCRIPT:
    return COMPONENT_SCRIPT_SLOT;
    break;

  case Component::eType::CAMERA:
    return COMPONENT_CAMERA_SLOT;
    break;

  case Component::eType::RIGIDBODY:
  case Component::eType::SOFTBODY:
    return COMPONENT_PHYSICS_BODY_SLOT;
    break;

  case Component::eType::BLOCK_COLLIDER:
  case Component::eType::SPHERE_COLLIDER:
  case Component::eType::MESH_COLLIDER:
    return COMPONENT_PHYSICS_COLLIDER_SLOT;
    break;

  case Component::eType::MESH_RENDERER:
    return COMPONENT_MESH_RENDERER_SLOT;
    break;

  default:
    return 0;
    break;
  }
}

void Scene::EnlistComponent(Component* pNewComponent)
{
  // Get type
  size_t type = pNewComponent->GetType();

  // Map type to slot
  size_t slotIndex = MapTypeToSlot(type);

  // Insert it there
  _activeComponentBySlots[slotIndex].insert(std::make_pair(pNewComponent->GetGuid(), pNewComponent));
}

void Scene::DelistComponent(Component* pNewComponent)
{
  // Get type
  size_t type = pNewComponent->GetType();

  // Map type to slot
  size_t slotIndex = MapTypeToSlot(type);

  // Insert it there
  _activeComponentBySlots[slotIndex].erase(pNewComponent->GetGuid());
}

#if !NEW_SSSEC_IMPLEMENTED

Entity* Scene::InsertEntity_(Entity* pEntityToInsert)
{
  _entities.insert(std::make_pair(pEntityToInsert->GetGuid(), pEntityToInsert));

  // If has Colliders, insert them into map as well.
  if (pEntityToInsert->GetBHasColliders())
  {
    InsertActiveColliders(pEntityToInsert);
  }

  return pEntityToInsert;
}

bool Scene::DeleteEntity_(Entity* pEntityToDelete)
{
  // If has Colliders, delete them.
  if (pEntityToDelete->GetBHasColliders())
  {
    DeleteActiveColliders(pEntityToDelete);
  }

  // Delete it from hash map.
  _entities.erase(pEntityToDelete->GetGuid());

  return true;
}


Entity* Scene::InsertActiveColliders(Entity* pEntityToInsert)
{
  auto entityColliders = pEntityToInsert->GetColliders();

  // Iteratre through all Colliders that this Entity has on it.
  for (auto && it : entityColliders)
  {
    _activeColliders.insert(std::make_pair(it.second->GetGuid(), it.second));
  }
  return pEntityToInsert;
}
Entity* Scene::DeleteActiveColliders(Entity* entityToDelete)
{
  auto entityColliders = entityToDelete->GetColliders();

  // Iteratre through all Colliders that this Entity has on it.
  for (auto && it : entityColliders)
  {
    _activeColliders.erase(it.second->GetGuid());
  }
  return entityToDelete;
}


Entity* Scene::InsertDirectionalLight(Entity* entityToInsert)
{
  // TODO: Increase light limit.
  if (_activePointLights.size() >= MAX_DIRECTIONAL_LIGHTS)
  {
    return nullptr;
  }

  _activeDirectionalLights.insert(std::make_pair(entityToInsert->GetGuid(), entityToInsert));
  return entityToInsert;
}

Entity* Scene::InsertActiveModel(Entity* entityToInsert)
{
  _activeModels.insert(std::make_pair(entityToInsert->GetGuid(), entityToInsert));
  return entityToInsert;
}

Entity* Scene::InsertPointLight(Entity* entityToInsert)
{
  // TODO: Increase light limit.
  if (_activePointLights.size() >= MAX_POINT_LIGHTS)
  {
    return nullptr;
  }

  _activePointLights.insert(std::make_pair(entityToInsert->GetGuid(), entityToInsert));
  return entityToInsert;
}

Entity* Scene::InsertSpotLight(Entity* entityToInsert)
{
  // TODO: Increase light limit.
  if (_activeSpotLights.size() >= MAX_SPOT_LIGHTS)
  {
    return nullptr;
  }
  _activeSpotLights.insert(std::make_pair(entityToInsert->GetGuid(), entityToInsert));
  return entityToInsert;
}

const std::unordered_map<size_t, Entity*>& Scene::GetActiveModelsRefConst() const
{
  return _activeModels;
}
const std::unordered_map<size_t, Collider*>& Scene::GetActiveColliders() const
{
  return _activeColliders;
}
const std::unordered_map<size_t, Entity*>& Scene::GetDirectionalLightsMapRefConst() const
{
  return _activeDirectionalLights;
}
const std::unordered_map<size_t, Entity*>& Scene::GetPointLightsMapRefConst() const
{
  return _activePointLights;
}

const std::unordered_map<size_t, Entity*>& Scene::GetSpotLightsMapRefConst() const
{
  return _activeSpotLights;
}


_Camera* Scene::CreateCamera(std::string_view cameraName, glm::vec3 positionVector, glm::vec3 startUpDirection, float startYaw, float startPitch)
{
  // TEMP
  // Camera has also input methods
  // It needs total restructure.
  //
  float moveSpeed = 5.0f;
  float turnSpeed = 1.0f;

  // Create new Camera instance.
  _Camera* pNewCamera = (_Camera*)_pEntityManager->CreateCamera(cameraName, positionVector, startUpDirection, startYaw, startPitch, moveSpeed, turnSpeed);

  pNewCamera->SetEntityName(cameraName);

  // TODO: Implement properly.
  _pEditorCamera = pNewCamera;

  return static_cast<_Camera*>(InsertEntity_(pNewCamera));
}

Quad* Scene::CreateQuad(
  std::string_view entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  dfloat width, dfloat height
)
{
  // Call EntityManager to create new Quad Entity.
  Quad* pNewQuad = (Quad*)_pEntityManager->CreateQuad(
    entityName,
    positionVector,
    rotationVector,
    scaleVector,
    width, height
  );


  // TODO: Make dynamic
  (*pNewQuad).SetBIsToRender(true);

  if ((*pNewQuad).GetBIsToRender())
  {
    InsertActiveModel(pNewQuad);
  }

  return static_cast<Quad*>(InsertEntity_(pNewQuad));
}



Block* Scene::_CreateBlock(
  std::string_view entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  dfloat width, dfloat height, dfloat length,
  bool bIsStatic
)
{
  // Call EntityManager to create new Quad Entity.
  Block* pNewBlock = (Block*)_pEntityManager->CreateBlock(
    entityName,
    positionVector,
    rotationVector,
    scaleVector,
    width, height, length,
    bIsStatic
  );


  // TODO: Make dynamic
  (*pNewBlock).SetBIsToRender(true);

  if ((*pNewBlock).GetBIsToRender())
  {
    InsertActiveModel(pNewBlock);
  }

  return static_cast<Block*>(InsertEntity_(pNewBlock));
}


WorldObject* Scene::CreateStaticModelFromFile(
  std::string_view entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  std::string_view filePath
)
{
  // Call EntityManager to create new WorldObject Entity.
  WorldObject* pNewEntity = (WorldObject*)_pEntityManager->CreateStaticModelFromFile(
    entityName,
    positionVector,
    rotationVector,
    scaleVector,
    filePath
  );


  // TODO: Make dynamic
  (*pNewEntity).SetBIsToRender(true);

  if ((*pNewEntity).GetBIsToRender())
  {
    InsertActiveModel(pNewEntity);
  }

  return static_cast<Block*>(InsertEntity_(pNewEntity));
}

_DirectionalLight* Scene::_CreateDirectionalLight
(
  std::string_view entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  glm::vec3 lightColour, glm::vec3 lightIntensities, 
  glm::vec3 shadowMapSize,
  glm::vec3 lightDirection
)
{

  _DirectionalLight* pMainLight = (_DirectionalLight*)_pEntityManager->CreateDirectionalLight(
    entityName,
    positionVector,          // Position vector
    rotationVector,          // rotation vector
    scaleVector,          // scale vector
    lightColour,          // Colour vector
    lightIntensities,          // Intensities
    shadowMapSize,    // Shadow dimensions
    lightDirection      // Light direction vector
  );

  pMainLight->SetEntityName(entityName);

  
  InsertDirectionalLight(pMainLight);

  return static_cast<_DirectionalLight*>(InsertEntity_(pMainLight));
  
}

_PointLight* Scene::CreatePointLight(
  std::string_view entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector, 
  glm::vec3 lightColour, glm::vec3 lightIntensities, glm::vec3 shadowMapSize, 
  glm::vec2 planeDimensions, glm::vec3 coefficients
)
{
  _PointLight* pMainLight = (_PointLight*)_pEntityManager->CreatePointLight(
    entityName,
    positionVector,          // Position vector
    rotationVector,          // rotation vector
    scaleVector,          // scale vector
    lightColour,          // Colour vector
    lightIntensities,          // Intensities
    shadowMapSize,    // Shadow dimensions
    planeDimensions,      // Light direction vector
    coefficients
  );

  pMainLight->SetEntityName(entityName);
  
  InsertPointLight(pMainLight);

  return static_cast<_PointLight*>(InsertEntity_(pMainLight));
}

_SpotLight* Scene::CreateSpotLight(
  std::string_view entityName,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector, 
  glm::vec3 lightColour, glm::vec3 lightIntensities, glm::vec3 shadowMapSize, 
  glm::vec2 planeDimensions, glm::vec3 coefficients, glm::vec3 lightDirection, 
  dfloat coneAngle
)
{
  _SpotLight* pMainLight = (_SpotLight*)_pEntityManager->CreateSpotLight(
    entityName,
    positionVector,          // Position vector
    rotationVector,          // rotation vector
    scaleVector,          // scale vector
    lightColour,          // Colour vector
    lightIntensities,          // Intensities
    shadowMapSize,    // Shadow dimensions
    planeDimensions,      // Light direction vector
    coefficients,
    lightDirection,
    coneAngle
  );

  pMainLight->SetEntityName(entityName);

  InsertSpotLight(pMainLight);

  return static_cast<_SpotLight*>(InsertEntity_(pMainLight));
}

#endif