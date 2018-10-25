#pragma once

#include "BaseModule.h"

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


private:

};

}