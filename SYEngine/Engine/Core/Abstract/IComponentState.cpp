#include "IComponentState.h"

using namespace SYE;

IComponentState::IComponentState():
  _state(eComponentState::Null)
{}

IComponentState::~IComponentState()
{
  _state = eComponentState::Null;
}

void IComponentState::SetComponentState(eComponentState newState)
{
  _state = newState;
  return;
}
eComponentState IComponentState::GetComponentState()
{
  return _state;
}