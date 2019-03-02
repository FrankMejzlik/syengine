#pragma once

#include <memory>


#include "common.h"
#include "BaseModule.h"
#include "Mesh.h"

// Submodules.
#include "MeshGenerator.h"


using namespace SYE;

namespace SYE {

class MeshManager :
  public BaseModule
{
public:
  MeshManager() = delete;

  MeshManager(BaseModule& parentModule, EngineContext* pEngineContext);
  ~MeshManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  std::pair< std::vector<dfloat>, std::vector<unsigned int> > GenerateBlockVerticesIndices(
    dfloat width, dfloat height, dfloat length
  )
  {
    return MESH_GENERATOR->GenerateBlockVerticesIndices(width, height, length);
  }

  std::pair< std::vector<dfloat>, std::vector<unsigned int> > GeneratePrismVerticesIndices(
    const Vector3f& p1, const Vector3f& p2, const Vector3f& p3, const Vector3f& p4,
    const Vector3f& p5, const Vector3f& p6, const Vector3f& p7, const Vector3f& p8
  )
  {
    return MESH_GENERATOR->GeneratePrismVerticesIndices(p1, p2, p3, p4, p5, p6, p7, p8);
  }
  
  std::pair< std::vector<dfloat>, std::vector<unsigned int> > GenerateQuadVerticesIndices(
    dfloat width, dfloat height
  )
  {
    return MESH_GENERATOR->GenerateQuadVerticesIndices(width, height);
  }

  std::pair< std::vector<dfloat>, std::vector<unsigned int> > GenerateSphereVerticesIndices(
    dfloat radius, size_t numSlices, size_t numStacks
  )
  {
    return MESH_GENERATOR->GenerateSphereVerticesIndices(radius, numSlices, numStacks);
  }

  std::unique_ptr<Mesh> GenerateMeshQuad(dfloat width, dfloat height);
  std::unique_ptr<Mesh> GenerateMeshBlock(dfloat width, dfloat height, dfloat length);


private:
  

};

}