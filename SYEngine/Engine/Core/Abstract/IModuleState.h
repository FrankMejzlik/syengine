#pragma once

#include "config_engine.h"

namespace SYE {

/**
* Interface for every main engine module. Giving it necessary things that modules must have.
*
* It gives module state attribute and state getters/setters.
*/
class IModuleState
{
public:
  IModuleState();
  virtual ~IModuleState();

protected:
  eModuleState _moduleState;

  void SetModuleState(eModuleState newState);
  eModuleState GetModuleState();

};

}

