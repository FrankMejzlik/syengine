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
    glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, bool isSolid);
  virtual ~Collider();

  const std::vector<unsigned int>& GetIndices()
  {
    return _pMesh->GetIndices();
  }

  const std::vector<GLfloat>& GetVertices()
  {
    return _pMesh->GetVertices();;
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
  bool _bIsSolid;

};

} // namespace SYE