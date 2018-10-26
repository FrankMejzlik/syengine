#include "Quad.h"



Quad::Quad(
  std::shared_ptr<ComponentManager> pComponentManager,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  bool bIsStatic,
  dfloat width, dfloat height
):
  WorldObject(pComponentManager, positionVector, rotationVector, scaleVector, bIsStatic)
{}


Quad::~Quad()
{}
