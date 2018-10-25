#pragma once

#include "BaseModule.h"

using namespace WeSp;

namespace WeSp {

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