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

  MeshManager(BaseModule &parentModule);
  ~MeshManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  std::unique_ptr<Mesh> GenerateMeshQuad(dfloat width, dfloat height);
  std::unique_ptr<Mesh> GenerateMeshBlock(dfloat width, dfloat height, dfloat length);


private:
  

};

}