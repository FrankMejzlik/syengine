#pragma once

#include "Command.h"


using namespace WeSp;

namespace WeSp {

class EngineApi;

/**
 * Interface for classes that needs to communicate with EngineAPI.
 */
class IUsesEngineAPI
{
public:
  IUsesEngineAPI();
  IUsesEngineAPI(std::shared_ptr<EngineApi> pEngineAPI);
  virtual ~IUsesEngineAPI();

protected:
  std::shared_ptr<EngineApi> _pEngineAPI;

};

}