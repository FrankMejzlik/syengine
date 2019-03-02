
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
#include "Entity.h"

#include "Engine.h"
#include "EntityManager.h"
#include "PhysicsEntity.h"
#include "PhysicsScene.h"
#include "EngineContext.h"
#include "SceneContext.h"

using namespace SYE;

Scene::Scene(EngineContext* pEngineContext, Engine* pEngine, Window* pTargetWindow, size_t sceneId) :
  IEngineContextInterface(pEngineContext),
  _pSceneContext(std::make_unique<SceneContext>(sceneId)),
  _pEngine(pEngine),
  _pMainWindow(pTargetWindow),
  _pEditorCamera(nullptr)
{
  // Attach this engine to Engine
  _pEngine->AttachScene(this);

  DLog(eLogType::Success, "Scene %d instantiated.", _pSceneContext->GetSceneId());
}

Scene::~Scene() noexcept
{
  DLog(eLogType::Success, "Scene %d destroyed.", _pSceneContext->GetSceneId());
}

Camera* Scene::GetEditorCamera() const
{
  return _pEditorCamera;
}


void Scene::SetPhysicsScenePtr(PhysicsScene* pPhysicsScene)
{
  _pPhysicsScene = pPhysicsScene;
}

PhysicsScene* Scene::GetPhysicsScenePtr() const
{
  return _pPhysicsScene;
}


std::pair<PhysicsBody*, Vector3f> Scene::Raycast(Vector3f from, Vector3f direction) const
{
  // If not valid physics scene
  if (_pPhysicsScene == nullptr)
  {
    PUSH_ENGINE_ERROR(eEngineError::PhysicalSceneNotSet, "Trying to do operation on PhysicsScene, but it's not valid.", "");

    return std::make_pair(nullptr, Vector3f(0.0f, 0.0f, 0.0f));
  }
  
  return _pPhysicsScene->Raycast(from, direction);
}



bool Scene::RemoveEntity(Entity* pEntityToDelete)
{
  // Detach it from Scene
  if (!DetachEntity(pEntityToDelete))
  {
    PUSH_EDITOR_ERROR(
      eEngineError::TryingToDeleteNonExistentEntityFromScene,
      "This Entity '" + std::to_string(pEntityToDelete->GetGuid()) + "' does not exist in Scene '" + std::to_string(GetGuid()) + "' and thus cannot be deleted.",
      ""
    );

    return false;
  }

  // Tell EntityManager to destroy it
  bool result = GetEntityManagerPtr()->DestroyEntity(pEntityToDelete);
  if (!result)
  {
    PUSH_EDITOR_ERROR(
      eEngineError::UnableToDeleteEntityBecauseDestructionFailed,
      "This Entity '" + std::to_string(pEntityToDelete->GetGuid()) + "' is detached from Scene '" + std::to_string(GetGuid()) + "' but destruction failed. It is still allocated.",
      ""
    );
  }

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
  Entity* pNewEntity = GetEntityManagerPtr()->CreateEntity<Entity>(this, nullptr);

  // Add Transform Component
  Transform* pTransform = pNewEntity->AddComponent<Transform>();
  pTransform->SetPosition(positionVector);
  pTransform->SetRotation(Vector3f(startYaw, startPitch, 0.0f));

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

  // Add new Entity to Scene instance
  Entity* pNewEntity = AddEntity<Entity>();

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

  return pNewEntity;
}


Entity* Scene::CreateBlock(
  Vector3f positionVector, Vector3f rotationVector, Vector3f scaleVector,
  dfloat width, dfloat height, dfloat length,
  bool isStatic,
  dfloat mass
)
{ 
  // Add new Entity to Scene instance
  Entity* pNewEntity = AddEntity<Entity>();
  {
    pNewEntity->SetIsStatic(isStatic);

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

    // Add Rigigbody Component
    Rigidbody* pRigidBody = pNewEntity->AddComponent<Rigidbody>();
    pRigidBody->SetIsKinematic(true);
    pRigidBody->SetMass(mass);
    {
      // Add Collider
      BlockCollider* pBlockCollider = pRigidBody->AddBlockCollider(width, height, length);
      pBlockCollider->SetLocalPosition(Vector3f(0.0f, 0.0f, 0.0f));
      pBlockCollider->SetLocalRotation(Vector3f(0.0f, 0.0f, 0.0f));
      pBlockCollider->SetLocalScale(Vector3f(1.0f, 1.0f, 1.0f));
    }
    pRigidBody->SaveComponent();
  }
  pNewEntity->SaveEntity();


  return pNewEntity;
}


Entity* Scene::CreateDirectionalLight(
  Vector3f positionVector, Vector3f rotationVector, Vector3f scaleVector,
  Vector3f colour, Vector3f intensities, Vector3u shadowDimensions,
  Vector3f direction,
  bool isStatic
)
{
  UNREFERENCED_PARAMETER(isStatic);

  // Add new Entity to Scene instance
  Entity* pNewEntity = AddEntity<Entity>();

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

  
  return pNewEntity;
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

  // Add new Entity to Scene instance
  Entity* pNewEntity = AddEntity<Entity>();

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


  return pNewEntity;
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

  // Add new Entity to Scene instance
  Entity* pNewEntity = AddEntity<Entity>();

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


  return pNewEntity;
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

  case Component::eType::RIGID_BODY:
  case Component::eType::SOFT_BODY:
    return COMPONENT_PHYSICS_BODY_SLOT;
    break;

  case Component::eType::BLOCK_COLLIDER:
  case Component::eType::SPHERE_COLLIDER:
  case Component::eType::CONVEX_MESH_COLLIDER:
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

void Scene::ShootBox(const Vector3f& cameraPosition, const Vector3f& direction) 
{
  // Create new Entity
  Entity* pBox = CreateBlock(
    cameraPosition, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f),
    1.0f, 1.0f, 1.0f,
    false,
    1.0f
  );

  // Calculate the velocity
  Vector3f velocity = Normalize(direction) * 25.0f;

  // Set the linear velocity of the box
  static_cast<btRigidBody*>(pBox->GetPhysicsBodyPtr()->GetPhysicsEntity()->GetCollisionObjectPtr())->setLinearVelocity(velocity);
}

bool Scene::RegisterComponent(Component* pNewComponent)
{
  // Get type
  size_t type = pNewComponent->GetType();

  // Map type to slot
  size_t slotIndex = MapTypeToSlot(type);

  // Insert it there
  auto result = _activeComponentBySlots[slotIndex].insert(std::make_pair(pNewComponent->GetGuid(), pNewComponent));

  // If already existed
  if (result.second == false)
  {
    PUSH_EDITOR_ERROR(
      eEngineError::RegisteredAlreadyExistingComponentToScene, 
      "This Component is already registered to Scene instance with ID " + GetGuid(), 
      ""
    );

    return false;
  }

  return true;
}

bool Scene::UnregisterComponent(Component* pNewComponent)
{
  // Get type
  size_t type = pNewComponent->GetType();

  // Map type to slot
  size_t slotIndex = MapTypeToSlot(type);

  // Insert it there
  size_t result = _activeComponentBySlots[slotIndex].erase(pNewComponent->GetGuid());

  return (result > 0);
}

bool Scene::AttachEntity(Entity* pEntity)
{
  // Insert it there
  auto result = _childEntities.insert(std::make_pair(pEntity->GetGuid(), pEntity));

  // If already existed
  if (result.second == false)
  {
    PUSH_EDITOR_ERROR(
      eEngineError::AttachingAlreadyExistingEntityToScene,
      "This Entity '" + std::to_string(pEntity->GetGuid()) + "' is already attached to Scene instance with ID " + std::to_string(GetGuid()),
      ""
    );

    return false;
  }

  return true;
}

bool Scene::DetachEntity(Entity* pEntity)
{
  auto result = _childEntities.erase(pEntity->GetGuid());

  return (result > 0);
}
