
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

/**
 * Common ancestor to all Engine modules.
 *
 * Ancestor to modules like InputManager, SceneManager etc.
 */
class BaseModule:
  public IModule, public IModuleState, public IErrorLogging, public IUsesEngineAPI
{
public:
  
  BaseModule() = delete;
  // Constructor for just root module - Engine.
  BaseModule(int magicNumber);
  // Constructor for other modules.
  BaseModule(BaseModule &parentModule);

  virtual ~BaseModule() = default;

  void SetEngineApiPointer(const EngineApi* const pEngineApi);

protected:
  BaseModule &_parentModule;
  const EngineApi* _pEngineApi;
  std::map<int, std::unique_ptr<BaseModule>> _subModules;

  // Just for ability to constrict Component before removing last bits of old architecture
  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS> _fake;

};

} // namespace SYE

#endif // #ifndef BASE_MODULE_H_