#pragma once

#include "common.h"
#include "Collider.h"
#include "Entity.h"
#include "ComponentManager.h"

namespace SYE
{

class BlockCollider :
  public Collider
{
public:
  BlockCollider() = delete;
  BlockCollider(
    Entity* pOwnerEntity, 
    const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, 
    std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots
  ) noexcept;
  virtual ~BlockCollider() noexcept = default;

  void SetDimensions(dfloat width, dfloat height, dfloat length);

  // Attributes
protected:
  dfloat _width;
  dfloat _height;
  dfloat _length;

};

} // namespace SYE