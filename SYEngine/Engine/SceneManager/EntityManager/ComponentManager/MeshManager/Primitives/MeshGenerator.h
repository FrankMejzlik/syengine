#pragma once

#include "common.h"
#include "BaseModule.h"
#include "Mesh.h"

namespace SYE 
{

class MeshGenerator:
  public BaseModule
{
public:
  MeshGenerator() = delete;

  MeshGenerator(BaseModule &parentModule);
  ~MeshGenerator();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  /**
   * Generates mesh for block.
   */
  std::shared_ptr<Mesh> GenerateMeshBlock(
    dfloat width, dfloat height, dfloat length,
    bool bAverageNormals
  );

  /**
   * Generates mesh for quad.
   */
  std::shared_ptr<Mesh> GenerateMeshQuad(
    dfloat width, dfloat height,
    bool bAverageNormals
  );
};

}