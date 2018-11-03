#include "Block.h"



Block::Block(
  std::shared_ptr<ComponentManager> pComponentManager,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  bool bIsStatic,
  dfloat width, dfloat height, dfloat length
):
  WorldObject(pComponentManager, positionVector, rotationVector, scaleVector, bIsStatic)
{
  // Generate appropriate mesh for this.
  std::shared_ptr<Mesh> pBlockMesh = pComponentManager->GenerateMeshBlock(width, height, length);


  std::shared_ptr<Texture> pTexture = pComponentManager->GetTextureManager()->GetDefaultTexture();

  // Create new model from this Mesh.
  // No Texture nor Shiniess provided so it will be created with default ones.
  std::shared_ptr<Entity> pThis = std::shared_ptr<Block>(this);
  
  _pModel = pComponentManager->CreateModel(pThis, pBlockMesh, pTexture);

}


Block::~Block()
{}
