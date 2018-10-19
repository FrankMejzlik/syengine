#include "IUsesEngineAPI.h"
#include "EngineAPI.h"

IUsesEngineAPI::~IUsesEngineAPI()
{}


IUsesEngineAPI::IUsesEngineAPI() :
  _pEngineAPI(nullptr)
{}

IUsesEngineAPI::IUsesEngineAPI(std::shared_ptr<EngineAPI> pEngineAPI) :
  _pEngineAPI(pEngineAPI)
{}
