#pragma once

namespace SYE 
{

class EngineContext
{
public:
  EngineContext();

  bool GetBShouldRun() const;
  void SetBShouldRun(bool newValue);

private:
  bool _bShouldRun;




public:
    /////////// VVVVVVVVVVVVVVVVVVVVVVVVVV
    static bool gTorchOn;
  const float toRadians = 3.14159265f / 180.0f;

};

} // namespace SYE
