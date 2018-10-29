#pragma once

#include "common.h"
#include "Collider.h"

namespace WeSp
{

class BlockCollider :
  public Collider
{
public:
  BlockCollider() = delete;

  BlockCollider(std::shared_ptr<Entity> pEntity);
  virtual ~BlockCollider();
};

} // namespace WeSp