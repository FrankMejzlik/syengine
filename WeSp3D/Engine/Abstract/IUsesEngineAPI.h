#pragma once

#include "Command.h"


using namespace WeSp;

namespace WeSp {

class EngineAPI;

/**
 * Interface for classes that needs to communicate with EngineAPI.
 */
class IUsesEngineAPI
{
public:
  IUsesEngineAPI();
  IUsesEngineAPI(std::shared_ptr<EngineAPI> pEngineAPI);
  virtual ~IUsesEngineAPI();

protected:
  std::shared_ptr<EngineAPI> _pEngineAPI;

};

}