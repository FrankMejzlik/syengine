#pragma once

#include "common.h"
#include "Command.h"


using namespace SYE;

namespace SYE {

class EngineApi;

/**
 * Interface for classes that needs to communicate with EngineAPI.
 */
class IUsesEngineApi
{
public:
  IUsesEngineApi();
  IUsesEngineApi(std::shared_ptr<EngineApi> pEngineAPI);
  virtual ~IUsesEngineApi();

protected:
  std::shared_ptr<EngineApi> _pEngineAPI;

};

}
