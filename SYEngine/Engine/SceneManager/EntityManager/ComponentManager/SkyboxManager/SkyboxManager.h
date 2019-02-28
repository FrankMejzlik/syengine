#pragma once

#include "BaseModule.h"

using namespace SYE;

namespace SYE {

class SkyboxManager :
  public BaseModule
{
public:
  SkyboxManager() = delete;

  SkyboxManager(BaseModule& parentModule, EngineContext* pEngineContext);
  ~SkyboxManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;


private:

};

}