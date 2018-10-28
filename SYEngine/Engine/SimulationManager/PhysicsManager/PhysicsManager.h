#pragma once

#include "BaseModule.h"

using namespace WeSp;

namespace WeSp {

class PhysicsManager :
  public BaseModule
{
public:
  PhysicsManager() = delete;

  PhysicsManager(BaseModule &parentModule);
  ~PhysicsManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;


private:

};

}