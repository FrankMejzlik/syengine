#pragma once

#include <map>
#include <memory>

#include "Logger.h"

namespace WeSp {

class InputManager;

/**
 * Interface for InputManager submodule. Giving it necessary things that modules must have.
 *
 * Giving it Initialize interface for setting up all common things (e.g. pointers to other module instances)
 */
class IInputManagerSubmodule
{
public:
  IInputManagerSubmodule() = delete;

  // Main modules can be childs only of Engine class
  IInputManagerSubmodule(InputManager* pParentInstance);
  virtual ~IInputManagerSubmodule();

  virtual bool Initialize(std::map<int, std::shared_ptr<IInputManagerSubmodule>> subModules);
  virtual bool Terminate();

protected:
  InputManager* _pParentInstance;
  std::map<int, std::shared_ptr<IInputManagerSubmodule>> _subModules;

};

}