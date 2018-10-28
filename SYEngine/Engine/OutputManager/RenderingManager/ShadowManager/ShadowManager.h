#pragma once

#include "BaseModule.h"

using namespace WeSp;

namespace WeSp {

class ShadowManager :
  public BaseModule
{
public:
  ShadowManager() = delete;

  ShadowManager(BaseModule &parentModule);
  ~ShadowManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;


private:

};

}