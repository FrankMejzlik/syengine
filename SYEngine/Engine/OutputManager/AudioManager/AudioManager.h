#pragma once


#include "BaseModule.h"

using namespace SYE;

namespace SYE {

class AudioManager :
  public BaseModule
{
public:
  AudioManager() = delete;

  AudioManager(BaseModule &parentModule);
  ~AudioManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;
};

}