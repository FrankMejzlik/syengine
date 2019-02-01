#include "Quad.h"



Quad::Quad(
  ComponentManager* pComponentManager,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  bool bIsStatic,
  dfloat width, dfloat height
):
  WorldObject(pComponentManager, positionVector, rotationVector, scaleVector, bIsStatic)
{
  // Generate appropriate mesh for this.
  std::unique_ptr<Mesh> pQuadMesh = pComponentManager->GenerateMeshQuad(width, height);


  std::unique_ptr<Texture> pTexture = pComponentManager->GetTextureManager()->GetDefaultTexture();

  // Create new model from this Mesh.
  // No Texture nor Shiniess provided so it will be created with default ones.
  
  _pModel = pComponentManager->CreateModel(this, std::move(pQuadMesh), std::move(pTexture));

}


Quad::~Quad()
{}
