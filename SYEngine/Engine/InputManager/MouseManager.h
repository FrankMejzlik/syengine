#pragma once

#include "BaseModule.h"

using namespace SYE;

namespace SYE {

class MouseManager :
  public BaseModule
{
public:
  MouseManager() = delete;

  MouseManager(BaseModule &parentModule);
  ~MouseManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;


private:

};

}