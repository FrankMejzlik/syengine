
#ifndef BASE_MODULE_H_
#define BASE_MODULE_H_

#include <map>
#include <memory>


#include "common.h"
#include "IModuleState.h"
#include "IErrorLogging.h"
#include "IUsesEngineAPI.h"
#include "IModule.h"


namespace SYE
{

// Forward declarations.
class EngineApi;

class BaseModule:
  public IModule, public IModuleState, public IErrorLogging, public IUsesEngineAPI
{
public:
  
  BaseModule() = delete;
  // Constructor for just root module - Engine.
  BaseModule(int magicNumber);
  // Constructor for other modules.
  BaseModule(BaseModule &parentModule);
  virtual ~BaseModule();

  void SetEngineApiPointer(const EngineApi* const pEngineApi);

protected:
  BaseModule &_parentModule;
  const EngineApi* _pEngineApi;
  std::map<int, std::shared_ptr<BaseModule>> _subModules;

};

} // namespace SYE

#endif // #ifndef BASE_MODULE_H_