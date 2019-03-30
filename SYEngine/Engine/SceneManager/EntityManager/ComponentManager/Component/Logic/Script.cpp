#include "Script.h"

#include "Scene.h"
#include "Transform.h"
#include "ScriptHandler.h"

using namespace SYE;

Script::Script(
  Entity* pOwnerEntity, Component* pOwnerComponent,
  eSlotIndex slotIndex, Component::eType type
) :
  Component(pOwnerEntity, pOwnerComponent, false, true, slotIndex, type),
  _pParent(nullptr)
{}


Script::~Script() noexcept
{}

void Script::OnCollision([[maybe_unused]] const PhysicsBody::Collision& collision)
{

}
  