#pragma once

namespace WeSp 
{

class EngineContext
{
public:
  EngineContext();
  virtual ~EngineContext();

  static bool gTorchOn;

protected:
  const float toRadians = 3.14159265f / 180.0f;

};

}