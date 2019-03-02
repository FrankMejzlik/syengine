
#include "Shininess.h"

using namespace SYE;

Shininess::Shininess(
  Entity* pOwnerEntity, Component* pOwnerComponent,
  eSlotIndex slotIndex, Component::eType type
) :
  Component(pOwnerEntity, pOwnerComponent, false, true, slotIndex, type),
  _specularIntensity(0.3f), _shininessIntensity(4)
{}


void Shininess::SetSpecularIntensity(dfloat newValue)
{
  _specularIntensity = newValue;
}

void Shininess::SetShininessIntensity(dfloat newValue)
{
  _shininessIntensity = newValue;
}

dfloat Shininess::GetSpecularIntensity() const
{
  return _specularIntensity;
}

dfloat Shininess::GetShininessIntensity() const
{
  return _shininessIntensity;
}