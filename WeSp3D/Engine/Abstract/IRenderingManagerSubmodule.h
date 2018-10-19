#pragma once

#include <map>

#include "Logger.h"

namespace WeSp {

class RenderingManager;

/**
 * Interface for RenderingManager module. Giving it necessary things that modules must have.
 *
 * Giving it Initialize interface for setting up all common things (e.g. pointers to other module instances)
 */
class IRenderingManagerSubmodule
{
public:
  IRenderingManagerSubmodule() = delete;

  // Main modules can be childs only of Engine class
  IRenderingManagerSubmodule(RenderingManager* pParentInstance);
  virtual ~IRenderingManagerSubmodule();

  virtual bool Initialize(std::map<int, std::shared_ptr<IRenderingManagerSubmodule>> subModules);
  virtual bool Terminate();

protected:
  RenderingManager* _pParentInstance;
  std::map<int, std::shared_ptr<IRenderingManagerSubmodule>> _subModules;

};

}