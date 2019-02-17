#include "PhysicsMaterial.h"

using namespace SYE;

PhysicsMaterial::PhysicsMaterial(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef):
  Component(pOwnerEntity, subModulesConstRef)
{
  _type = eType::PHYSICS_MATERIAL;
}

PhysicsMaterial::~PhysicsMaterial()
{}
