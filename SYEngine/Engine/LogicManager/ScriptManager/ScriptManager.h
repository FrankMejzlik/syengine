#pragma once

#include "BaseModule.h"

using namespace SYE;

namespace SYE {

class ScriptManager :
  public BaseModule
{
public:
  ScriptManager() = delete;

  ScriptManager(BaseModule &parentModule);
  ~ScriptManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;


private:

};

}