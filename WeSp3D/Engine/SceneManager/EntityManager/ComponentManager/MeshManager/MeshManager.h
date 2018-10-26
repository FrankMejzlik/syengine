#pragma once

#include <memory>


#include "common.h"
#include "BaseModule.h"
#include "Mesh.h"

// Submodules.
#include "MeshGenerator.h"


using namespace WeSp;

namespace WeSp {

class MeshManager :
  public BaseModule
{
public:
  MeshManager() = delete;

  MeshManager(BaseModule &parentModule);
  ~MeshManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  std::shared_ptr<Mesh> GenerateMeshQuad(dfloat width, dfloat height);


private:
  

};

}