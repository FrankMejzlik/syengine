#include "Transform.h"

#include "Entity.h"
#include "PhysicsBody.h"
#include "PhysicsEntity.h"

#pragma warning(push, 1)
#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>
#pragma warning(pop)

using namespace SYE;

Transform::Transform(
  Entity* pOwnerEntity, Component* pOwnerComponent,
  eSlotIndex slotIndex, Component::eType type
) :
  Component(
    pOwnerEntity, pOwnerComponent,
    true, true,
    slotIndex, type
  ),
  _origin(Vector3f(0.0f, 0.0f, 0.0f)),
  _position(Vector3f(0.0f, 0.0f, 0.0f)),
  _rotation(Vector3f(0.0f, 0.0f, 0.0f)),
  _scale(Vector3f(1.0f, 1.0f, 1.0f)),
  _worldUp(0.0f, 1.0f, 0.0f)
{
}

Transform::~Transform() noexcept
{}


void Transform::SetOrigin(const Vector3f& origin)
{
  _origin = origin;
}

void Transform::SetOrigin(Vector3f&& origin)
{
  _origin = std::move(origin);
}

const Vector3f& Transform::GetOrigin() const
{
  return _origin;
}

void Transform::SetRotation(const Vector3f& rotation) 
{ 
  // Set rotation angles
  _rotation = rotation; 

  RecalcDirection();
  UpdatePhysBody();
}

void Transform::SetRotation(Vector3f&& rotation)
{
  // Set rotation angles
  _rotation = std::move(rotation);

  RecalcDirection();
  UpdatePhysBody();
}

void Transform::RecalcDirection()
{
  // Recalculate directions
  _zDir.SetX(cos(_rotation.GetX()) * cos(_rotation.GetY()));
  _zDir.SetY(sin(_rotation.GetY()));
  _zDir.SetZ(sin(_rotation.GetX()) * cos(_rotation.GetY()));
  _zDir = Normalize(_zDir);

  _xDir = Normalize(Cross(_worldUp, _zDir));
  _yDir = Normalize(Cross(_zDir, _xDir));
}

void Transform::UpdatePhysBody()
{
  PhysicsBody* pBody = GetPhysicsBody();

  if (!pBody)
  {
    return;
  }

  glm::mat4 worldTransform = GetModelToWorldMatrix();

  glm::vec3 scale;
  glm::quat rotation;
  glm::vec3 translation;
  glm::vec3 skew;
  glm::vec4 perspective;
  glm::decompose(worldTransform, scale, rotation, translation, skew, perspective);

 
  pBody->GetPhysicsEntity()->SetWorldTransform(translation, rotation);
}

glm::mat4 Transform::GetModelToWorldMatrix() const
{
  // Initialize identity
  glm::mat4 modelToWorldMatrix = std::move(glm::mat4(1.0f));

  // Last transform is to put everything back due to origin transform
  modelToWorldMatrix = glm::translate(modelToWorldMatrix, -(GetTransformPtr()->GetOrigin().GetData()));

  // Lastly transform
  modelToWorldMatrix = glm::translate(modelToWorldMatrix, GetTransformPtr()->GetPosition().GetData());
  // Rotate X
  modelToWorldMatrix = glm::rotate(modelToWorldMatrix, GetTransformPtr()->GetRotation().GetZ(), glm::vec3(0.0f, 0.0f, 1.0f));
  // Rotate Y
  modelToWorldMatrix = glm::rotate(modelToWorldMatrix, GetTransformPtr()->GetRotation().GetY(), glm::vec3(0.0f, 1.0f, 0.0f));
  // Rotate Z
  modelToWorldMatrix = glm::rotate(modelToWorldMatrix, GetTransformPtr()->GetRotation().GetX(), glm::vec3(1.0f, 0.0f, 0.0f));
  // Scale first
  modelToWorldMatrix = glm::scale(modelToWorldMatrix, GetTransformPtr()->GetScale().GetData());

  // Apply inverse origin translation first
  modelToWorldMatrix = glm::translate(modelToWorldMatrix, GetTransformPtr()->GetOrigin().GetData());

  return modelToWorldMatrix;
}