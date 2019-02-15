#include "Rigidbody.h"

using namespace SYE;

Rigidbody::Rigidbody(Entity* pOwnerEntity) noexcept:
  Component(pOwnerEntity)
{}


Rigidbody::~Rigidbody() noexcept
{}
