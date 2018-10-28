#include "IModuleState.h"

using namespace WeSp;

IModuleState::IModuleState():
  _moduleState(eModuleState::Null)
{}


IModuleState::~IModuleState()
{
  _moduleState = eModuleState::Null;
}

void IModuleState::SetModuleState(eModuleState newState)
{
  _moduleState = newState;
  return;
}

eModuleState IModuleState::GetModuleState()
{
  return _moduleState;
}
