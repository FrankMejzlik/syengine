#include "Component.h"

using namespace SYE;


Component::Component(std::shared_ptr<Entity> pEntity) :
  _pEntity(pEntity)
{
}

Component::~Component()
{
}

