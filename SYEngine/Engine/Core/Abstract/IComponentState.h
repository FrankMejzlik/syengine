#pragma once

enum class eComponentState
{
  Null,
  Ready,
  Error
};

namespace SYE {

class IComponentState
{
public:
  IComponentState();
  ~IComponentState();

  void SetComponentState(eComponentState newState);
  eComponentState GetComponentState();

private:
  eComponentState _state;
};

}