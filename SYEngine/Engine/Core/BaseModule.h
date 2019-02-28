
#ifndef BASE_MODULE_H_
#define BASE_MODULE_H_

#include <map>
#include <memory>
#include <array>

#include "common.h"
#include "config_components.h"
#include "IModuleState.h"
#include "IErrorLogging.h"
#include "IUsesEngineAPI.h"
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
  public IModule, public IModuleState, public IErrorLogging, public IUsesEngineAPI
{
  // Structs
public:
  /** Allow Engine class to set pointer to owning EngineContext ptr */
  friend class Engine;

  // Methods
public:
  BaseModule() = delete;
  // Constructor for just root module - Engine.
  BaseModule(int magicNumber);
  // Constructor for other modules.
  BaseModule(BaseModule& parentModule, EngineContext* pEngineContext);
  virtual ~BaseModule() noexcept = default;

  
  void SetEngineApiPointer(const EngineApi* const pEngineApi);

  std::map<int, std::unique_ptr<BaseModule>>& GetSubModulesRef() { return _subModules; }
  BaseModule& GetParentModuleRef() { return _parentModule; }
  
  EngineContext* GetEngineContextPtr() const { return _pEngineContext; };
  
private:
  void SetEngineContextPtr(EngineContext* pEngineContext) { _pEngineContext = pEngineContext; }

protected:
  BaseModule& _parentModule;
  EngineContext* _pEngineContext;
  const EngineApi* _pEngineApi;
  std::map<int, std::unique_ptr<BaseModule>> _subModules;

  // Just for ability to construct Component before removing last bits of old architecture
  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS> _fake;

};

} // namespace SYE

#endif // #ifndef BASE_MODULE_H_