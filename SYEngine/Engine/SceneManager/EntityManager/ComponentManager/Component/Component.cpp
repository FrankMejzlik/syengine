#include "Component.h"

using namespace WeSp;


Component::Component(std::shared_ptr<Entity> pEntity) :
  _pEntity(pEntity)
{
}

Component::~Component()
{
}

