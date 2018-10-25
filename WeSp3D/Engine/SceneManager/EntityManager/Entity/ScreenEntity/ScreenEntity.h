#pragma once
#include "Entity.h"

using namespace WeSp;

namespace WeSp
{
/**
 * Class representing entities that appear as 2D objects relative to screen.
 */
class ScreenEntity :
  public Entity
{
public:
  ScreenEntity();
  virtual ~ScreenEntity();
};

}