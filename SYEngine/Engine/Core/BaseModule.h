
#ifndef BASE_MODULE_H_
#define BASE_MODULE_H_

#include <map>
#include <memory>
#include <array>

#include "common.h"
#include "config_components.h"
#include "IModuleState.h"
#include "IErrorLogging.h"
#include "IUsesEngineApi.h"
#include "IModule.h"

namespace SYE
{

// Forward declarations
class Component;
class EngineApi;
class EngineContext;
class Engine;

/**
 * Common ancestor to all Engine modules.
 *
 * Ancestor to modules like InputManager, SceneManager etc.
 */
class BaseModule:
  public IModule, public IModuleState, public IErrorLogging, public IUsesEngineApi
{
  // Structs
public:
  //! Allow Engine class to set pointer to owning EngineContext ptr
  friend class Engine;

  // Methods
public:
  BaseModule() = delete;
  // Constructor for just root module - Engine.
  BaseModule(int magicNumber);
  // Constructor for other modules.
  BaseModule(BaseModule& parentModule, EngineContext* pEngineContext);
  virtual ~BaseModule() noexcept = default;

  /*!
   * Terminates all active things related to currently active Scene/Game
   */
  virtual void TerminateGame();
  
  void SetEngineApiPointer(const EngineApi* const pEngineApi);

  std::map<int, std::unique_ptr<BaseModule>>& GetSubModulesRef() { return _subModules; }
  BaseModule& GetParentModuleRef() { return _parentModule; }
  
  EngineContext* GetEngineContextPtr() const { return _pEngineContext; };
  
protected:
  void EnlistSubmodulesToEngineContext();

private:
  void SetEngineContextPtr(EngineContext* pEngineContext) { _pEngineContext = pEngineContext; }

protected:
  BaseModule& _parentModule;
  EngineContext* _pEngineContext;
  const EngineApi* _pEngineApi;
  std::map<int, std::unique_ptr<BaseModule>> _subModules;


};

} // namespace SYE

#endif // #ifndef BASE_MODULE_H_
