#pragma once

#include <GLM/glm.hpp>

#include "common.h"
#include "Component.h"
#include "Mesh.h"
#include "Entity.h"

namespace SYE
{

class Collider :
  public Component
{
public:
  Collider() = delete;
  
  Collider(std::shared_ptr<Entity> pEntity);
  Collider(std::shared_ptr<Entity> pEntity, std::shared_ptr<Mesh> mesh,
    glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, bool bIsStatic, bool bIsSolid);
  virtual ~Collider();

  void SetOwnerEntityPosition(dfloat x, dfloat y, dfloat z)
  {
    _pEntity->SetPositionVector(glm::vec3(x, y, z));
  }

  void SetOwnerEntityRotation(dfloat rotX, dfloat rotY, dfloat rotZ)
  {
    _pEntity->SetRotationVector(glm::vec3(rotX, rotY, rotZ));
  }

  const std::vector<unsigned int>& GetIndices()
  {
    return _pMesh->GetIndices();
  }

  const std::vector<GLfloat>& GetVertices()
  {
    return _pMesh->GetVertices();;
  }

  const glm::vec3& GetAbsolutePositionConstRef() const
  {
    return _absolutePosition;
  }

  const glm::vec3& GetAbsoluteRotationConstRef() const
  {
    return _absoluteRotation;
  }

  const glm::vec3& GetAbsoluteScaleConstRef() const
  {
    return _absoluteScale;
  }

  bool GetBIsStatic() const
  {
    return _bIsStatic;
  }
  bool GetBIsSolid() const
  {
    return _bIsSolid;
  }

protected:
  // Position relative to parent object
  glm::vec3 _position;
  glm::vec3 _rotation;
  glm::vec3 _scale;

  // Values relative to world origin
  glm::vec3 _absolutePosition;
  glm::vec3 _absoluteRotation;
  glm::vec3 _absoluteScale;

  std::shared_ptr<Mesh> _pMesh;
  bool _bIsStatic;
  bool _bIsSolid;


  void RecalculateAbsolutePosition()
  {
    _absolutePosition = _pEntity->GetPositionVectorRefConst() + _position;
  }

  void RecalculateAbsoluteRotation()
  {
    _absoluteRotation = _pEntity->GetRotationVectorRefConst() + _rotation;
  }

};

} // namespace SYE