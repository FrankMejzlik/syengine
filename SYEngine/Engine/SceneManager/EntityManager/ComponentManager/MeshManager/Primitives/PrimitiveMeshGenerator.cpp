
#include "PrimitiveMeshGenerator.h"

using namespace SYE;

std::shared_ptr<Mesh> PrimitiveMeshGenerator::GenerateBlockMesh(
  float width, float height, float length,
  bool bAverageNormals
  )
{
  // Generate vertices vector.
  std::vector<float> blockVertices = 
  {
    // x      y         z           u    v       nx     ny   nz
    -width, height, -length,		  0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
    -width, -height, -length,	    0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
    width, height, -length,		      0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
    width, -height, -length,		    0.0f, 0.0f,		0.0f, 0.0f, 0.0f,

    -width, height, length,		    0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
    width, height, length,		  0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
    -width, -height, length,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
    width, -height, length,		  0.0f, 0.0f,		0.0f, 0.0f, 0.0f
  };

  // Create indices vector.
  std::vector<unsigned int>  blockIndices = 
  {
    // front
    0, 1, 2,
    2, 1, 3,
    // right
    2, 3, 5,
    5, 3, 7,
    // back
    5, 7, 4,
    4, 7, 6,
    // left
    4, 6, 0,
    0, 6, 1,
    // top
    4, 0, 5,
    5, 0, 2,
    // bottom
    1, 6, 3,
    3, 6, 7
  };

  // Mesh
  std::shared_ptr<Mesh> pBlockMesh = std::make_shared<Mesh>(nullptr, _subModules, _fake);    
  pBlockMesh->CreateMesh(blockVertices, blockIndices, bAverageNormals);

  return pBlockMesh;
}
