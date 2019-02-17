#include "Transform.h"

#include "Entity.h"

using namespace SYE;

Transform::Transform(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots) noexcept:
  Component(
    pOwnerEntity, subModulesConstRef, primaryComponentSlots,
    true, true,
    TRANSFORM
  ),
  _position(Vector3f(0.0f, 0.0f, 0.0f)),
  _rotation(Vector3f(0.0f, 0.0f, 0.0f)),
  _scale(Vector3f(1.0f, 1.0f, 1.0f))
{
  _type = eType::TRANSFORM;
}

Transform::Transform(
  Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots,
  Vector3f position,
  Vector3f rotation,
  Vector3f scale
) noexcept :
  Component(pOwnerEntity, subModulesConstRef, primaryComponentSlots),
  _position(position),
  _rotation(rotation),
  _scale(scale)
{
  _type = eType::TRANSFORM;

}

Transform::~Transform() noexcept
{}
