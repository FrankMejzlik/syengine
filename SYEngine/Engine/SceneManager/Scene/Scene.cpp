
#include "Scene.h"

#include "Transform.h"
#include "MeshRenderer.h"
#include "Rigidbody.h"
#include "BlockCollider.h"
#include "Texture.h"
#include "Material.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Camera.h"
#include "Mesh.h"

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

Camera* Scene::GetEditorCamera() const
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

  return pEntityToInsert;
}

bool Scene::DeleteEntity(Entity* pEntityToDelete)
{

  // Delete it from hash map.
  _entities.erase(pEntityToDelete->GetGuid());

  return true;
}

Entity* Scene::CreateCamera(
  Vector3f positionVector, 
  Vector3f startUpDirection, dfloat startYaw, dfloat startPitch,
  bool isEditor
)
{
  UNREFERENCED_PARAMETER(positionVector);
  UNREFERENCED_PARAMETER(startUpDirection);
  UNREFERENCED_PARAMETER(startYaw);
  UNREFERENCED_PARAMETER(startPitch);

  // Call EntityManager to create new Quad Entity.
  Entity* pNewEntity = _pEntityManager->CreateEntity(this);

  // Add Transform Component
  Transform* pTransform = pNewEntity->AddComponent<Transform>();
  pTransform->SetPosition(positionVector);

  // Add Camera Component
  Camera* pCamera = pNewEntity->AddComponent<Camera>();
  if (isEditor)
  {
    pCamera->SetCameraMode(Camera::eCameraModes::EDITOR_CAMERA);

    // TODO: Remove this
    _pEditorCamera = pCamera;
  }
  
  return pNewEntity;
}

Entity* Scene::CreateQuad(
  Vector3f positionVector, Vector3f rotationVector, Vector3f scaleVector,
  dfloat width, dfloat height,
  bool isStatic
)
{ 
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

  return InsertEntity(pNewEntity);
}


Entity* Scene::CreateBlock(
  Vector3f positionVector, Vector3f rotationVector, Vector3f scaleVector,
  dfloat width, dfloat height, dfloat length,
  bool isStatic
)
{ 
  UNREFERENCED_PARAMETER(isStatic);

  // Call EntityManager to create new Quad Entity.
  Entity* pNewEntity = _pEntityManager->CreateEntity(this);
  pNewEntity->SetIsStatic(false);
  
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

  return InsertEntity(pNewEntity);
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

  
  return InsertEntity(pNewEntity);
}

Entity* Scene::CreatePointLight(
  Vector3f positionVector, Vector3f rotationVector, Vector3f scaleVector,
  Vector3f colour, Vector3f intensities, Vector3u shadowDimensions,
  dfloat nearPlane, dfloat farPlane,
  Vector3f coefficients,
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
  PointLight* pLight = pNewEntity->AddComponent<PointLight>();
  pLight->SetColour(colour.GetData());
  pLight->SetInensities(intensities.GetData());
  pLight->SetShadowDimensions(shadowDimensions.GetData(), nearPlane, farPlane);
  pLight->SetCoeficients(coefficients);


  return InsertEntity(pNewEntity);
}


Entity* Scene::CreateSpotLight(
  Vector3f positionVector, Vector3f rotationVector, Vector3f scaleVector,
  Vector3f colour, Vector3f intensities, Vector3u shadowDimensions,
  dfloat nearPlane, dfloat farPlane,
  Vector3f coefficients,
  Vector3f direction,
  dfloat coneAngle,
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
  SpotLight* pLight = pNewEntity->AddComponent<SpotLight>();
  pLight->SetColour(colour.GetData());
  pLight->SetInensities(intensities.GetData());
  pLight->SetShadowDimensions(shadowDimensions.GetData(), nearPlane, farPlane);
  pLight->SetCoeficients(coefficients);
  pLight->SetLightDirection(direction);
  pLight->SetConeAngle(coneAngle);


  return InsertEntity(pNewEntity);
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

  case Component::eType::SCRIPT_HANDLER:
    return COMPONENT_SCRIPT_HANDLER_SLOT;
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
