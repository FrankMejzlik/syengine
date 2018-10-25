#pragma once

#include "BaseModule.h"

using namespace WeSp;

namespace WeSp {

class ShaderManager :
  public BaseModule
{
public:
  ShaderManager() = delete;

  ShaderManager(BaseModule &parentModule);
  ~ShaderManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;


private:

};

}