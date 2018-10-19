#pragma once

#include <map>
#include <memory>

#include "Logger.h"

namespace WeSp {

class Engine;

/**
 * Interface for every main engine module and submodule. Giving it necessary things that modules must have.
 *
 * Giving it Initialize interface for setting up all common things (e.g. pointers to other module instances)
 */
class IMainEngineModule
{
public:
  IMainEngineModule() = delete;

  // Main modules can be childs only of Engine class
  IMainEngineModule(Engine* pParentInstance);
  virtual ~IMainEngineModule();

  virtual bool Initialize(std::map<int, std::shared_ptr<IMainEngineModule>> modules);
  virtual bool Terminate();

protected:
  Engine* _pParentInstance;
  std::map<int, std::shared_ptr<IMainEngineModule>> _modules;
  

};

}