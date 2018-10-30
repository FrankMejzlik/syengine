#pragma once

#include <vector>
#include <memory>


#include "MeshGenerator.h"

namespace SYE
{

class PrimitiveMeshGenerator:
  public MeshGenerator
{
public:
  /**
   * Generates mesh for block.
   */
  std::shared_ptr<Mesh> GenerateBlockMesh(
    float width, float height, float length,
    bool bAverageNormals
  );

  /**
   * Generates mesh for quad.
   */
  std::shared_ptr<Mesh> GenerateQuadkMesh(
    float width, float height,
    bool bAverageNormals
  );


};

} // namespace SYE
