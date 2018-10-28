#pragma once


#include "BaseModule.h"

using namespace WeSp;

namespace WeSp {

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