#pragma once

#pragma warning(push, 1)
#include <GLM/glm.hpp>
#pragma warning(pop)

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
  
  Collider(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef);
  Collider(
    Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, 
    std::unique_ptr<Mesh>&& mesh,
    glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, 
    bool bIsStatic, bool bIsSolid
  );
  virtual ~Collider();

  void SetOwnerEntityPosition(dfloat x, dfloat y, dfloat z)
  {
    _pOwnerEntity->SetPositionVector(glm::vec3(x, y, z));
  }

  void SetOwnerEntityRotation(dfloat rotX, dfloat rotY, dfloat rotZ)
  {
    _pOwnerEntity->SetRotationVector(glm::vec3(rotX, rotY, rotZ));
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

  std::unique_ptr<Mesh> _pMesh;
  bool _bIsStatic;
  bool _bIsSolid;


  void RecalculateAbsolutePosition()
  {
    _absolutePosition = _pOwnerEntity->GetPositionVectorRefConst() + _position;
  }

  void RecalculateAbsoluteRotation()
  {
    _absoluteRotation = _pOwnerEntity->GetRotationVectorRefConst() + _rotation;
  }

};

} // namespace SYE