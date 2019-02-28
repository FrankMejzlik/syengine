#pragma once

#include "BaseModule.h"

using namespace SYE;

namespace SYE {

class AnimationManager :
  public BaseModule
{
public:
  AnimationManager() = delete;

  AnimationManager(BaseModule& parentModule, EngineContext* pEngineContext);
  ~AnimationManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;


private:

};

}