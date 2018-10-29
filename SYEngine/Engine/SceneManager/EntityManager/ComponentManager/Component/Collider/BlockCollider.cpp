#include "BlockCollider.h"

using namespace WeSp;

BlockCollider::BlockCollider(std::shared_ptr<Entity> pEntity) :
  Collider(pEntity)
{

}

BlockCollider::~BlockCollider()
{}
