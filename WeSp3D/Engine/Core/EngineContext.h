#pragma once

namespace WeSp 
{

class EngineContext
{
public:
  EngineContext();

  bool GetBShouldRun();

private:
  bool _bShouldRun;




public:
    /////////// VVVVVVVVVVVVVVVVVVVVVVVVVV
    static bool gTorchOn;
  const float toRadians = 3.14159265f / 180.0f;

};

} // namespace WeSp