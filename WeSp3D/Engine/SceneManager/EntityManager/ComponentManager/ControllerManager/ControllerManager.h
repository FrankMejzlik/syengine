#pragma once

#include "BaseModule.h"

using namespace WeSp;

namespace WeSp {

class ControllerManager :
  public BaseModule
{
public:
  ControllerManager() = delete;

  ControllerManager(BaseModule &parentModule);
  ~ControllerManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;


private:

};

}