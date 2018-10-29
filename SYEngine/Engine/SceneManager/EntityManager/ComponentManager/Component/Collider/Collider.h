#pragma once

#include <GLM/glm.hpp>

#include "common.h"
#include "Component.h"
#include "Mesh.h"

namespace WeSp
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
protected:
  // Position relative to parent object
  glm::vec3 _position;
  glm::vec3 _rotation;
  glm::vec3 _scale;

  std::shared_ptr<Mesh> _pMesh;
  bool _bIsSolid;

};

} // namespace WeSp