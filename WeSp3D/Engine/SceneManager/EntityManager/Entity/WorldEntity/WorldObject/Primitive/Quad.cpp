#include "Quad.h"



Quad::Quad(
  std::shared_ptr<ComponentManager> pComponentManager,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  bool bIsStatic,
  dfloat width, dfloat height
):
  WorldObject(pComponentManager, positionVector, rotationVector, scaleVector, bIsStatic)
{
  // Generate appropriate mesh for this.
  std::shared_ptr<Mesh> pQuadMesh = pComponentManager->GenerateMeshQuad(width, height);

  // Create new model from this Mesh.
  // No Texture nor Shiniess provided so it will be created with default ones.
  _pModel = pComponentManager->CreateModel(pQuadMesh);

}


Quad::~Quad()
{}
