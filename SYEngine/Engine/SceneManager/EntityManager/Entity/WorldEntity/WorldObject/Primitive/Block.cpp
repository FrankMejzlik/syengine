#include "Block.h"



Block::Block(
  ComponentManager* pComponentManager,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  bool bIsStatic,
  dfloat width, dfloat height, dfloat length
):
  WorldObject(pComponentManager, positionVector, rotationVector, scaleVector, bIsStatic)
{
  // Generate appropriate mesh for this.
  std::unique_ptr<Mesh> pBlockMesh = pComponentManager->GenerateMeshBlock(width, height, length);


  std::unique_ptr<Texture> pTexture = pComponentManager->GetTextureManager()->CreateDefaultTexture();

  // Create new model from this Mesh.
  // No Texture nor Shiniess provided so it will be created with default ones.
  
  _pModel = pComponentManager->CreateModel(this, std::move(pBlockMesh), std::move(pTexture));

}


Block::~Block()
{}
