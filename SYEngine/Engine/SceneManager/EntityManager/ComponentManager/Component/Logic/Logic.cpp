#include "Logic.h"

using namespace SYE;

Logic::Logic(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef):
  Component(pOwnerEntity, subModulesConstRef)
{
  _type = eType::LOGIC;
}

Logic::~Logic()
{}
