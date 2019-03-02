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
  MeshGenerator(BaseModule& parentModule, EngineContext* pEngineContext);
  ~MeshGenerator() noexcept;

  virtual bool Initialize() override;
  virtual bool Terminate() override;


  std::pair< std::vector<dfloat>, std::vector<unsigned int> > GenerateBlockVerticesIndices(
    dfloat width, dfloat height, dfloat length
  );
  std::pair< std::vector<dfloat>, std::vector<unsigned int> > GenerateQuadVerticesIndices(
    dfloat width, dfloat height
  );
  std::pair< std::vector<dfloat>, std::vector<unsigned int> > GenerateSphereVerticesIndices(
    dfloat radius, size_t numSlices, size_t numStacks
  );

  std::pair< std::vector<dfloat>, std::vector<unsigned int> > GeneratePrismVerticesIndices(
    const Vector3f& p1, const Vector3f& p2, const Vector3f& p3, const Vector3f& p4,
    const Vector3f& p5, const Vector3f& p6, const Vector3f& p7, const Vector3f& p8
  );

};

}