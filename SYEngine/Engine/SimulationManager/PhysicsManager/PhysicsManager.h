#pragma once

#include "BaseModule.h"

using namespace SYE;

namespace SYE {

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