#pragma once

#include "BaseModule.h"

using namespace WeSp;

namespace WeSp {

class SkyboxManager :
  public BaseModule
{
public:
  SkyboxManager() = delete;

  SkyboxManager(BaseModule &parentModule);
  ~SkyboxManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;


private:

};

}