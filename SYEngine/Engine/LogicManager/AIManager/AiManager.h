#pragma once

#include "BaseModule.h"

using namespace SYE;

namespace SYE {

class AiManager :
  public BaseModule
{
public:
  AiManager() = delete;

  AiManager(BaseModule &parentModule);
  ~AiManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;


private:

};

}