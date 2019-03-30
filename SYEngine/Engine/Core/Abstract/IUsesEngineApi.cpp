
#include "IUsesEngineApi.h"
#include "EngineApi.h"

IUsesEngineAPI::~IUsesEngineAPI()
{}


IUsesEngineAPI::IUsesEngineAPI() :
  _pEngineAPI(nullptr)
{}

IUsesEngineAPI::IUsesEngineAPI(std::shared_ptr<EngineApi> pEngineAPI) :
  _pEngineAPI(pEngineAPI)
{}
