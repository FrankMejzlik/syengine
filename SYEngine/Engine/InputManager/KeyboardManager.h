#pragma once

#include "BaseModule.h"

using namespace SYE;

namespace SYE {

class KeyboardManager :
  public BaseModule
{
public:
  KeyboardManager() = delete;

  KeyboardManager(BaseModule &parentModule);
  ~KeyboardManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;


private:

};

}