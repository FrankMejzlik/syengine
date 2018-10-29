#include "Collider.h"

using namespace WeSp;

Collider::Collider(std::shared_ptr<Entity> pEntity):
  Component(pEntity)
{

}


Collider::~Collider()
{}
