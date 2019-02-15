#include "Transform.h"

using namespace SYE;

Transform::Transform(Entity* pOwnerEntity) noexcept:
  Component(pOwnerEntity)
{}


Transform::~Transform() noexcept
{}
