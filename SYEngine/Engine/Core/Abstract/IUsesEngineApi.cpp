
#include "IUsesEngineApi.h"
#include "EngineApi.h"

IUsesEngineApi::~IUsesEngineApi()
{}


IUsesEngineApi::IUsesEngineApi() :
  _pEngineAPI(nullptr)
{}

IUsesEngineApi::IUsesEngineApi(std::shared_ptr<EngineApi> pEngineAPI) :
  _pEngineAPI(pEngineAPI)
{}
