#pragma once

namespace SYE 
{

class EngineContext
{
public:
  EngineContext();

  bool ShouldRun() const;
  void SetShouldRun(bool newValue);

private:
  bool _shouldRun;


public:
};

} // namespace SYE
