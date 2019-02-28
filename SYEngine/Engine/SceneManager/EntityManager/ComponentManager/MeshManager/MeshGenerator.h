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

};

}