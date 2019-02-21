#include "Script.h"

#include "Scene.h"
#include "Transform.h"
#include "ScriptHandler.h"

using namespace SYE;

Script::Script(
  Entity* pOwnerEntity, 
  const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, 
  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots
) noexcept :
  Component(pOwnerEntity, subModulesConstRef, primaryComponentSlots, false),
  _pParent(nullptr)
{
  _type = eType::SCRIPT;
}


Script::~Script() noexcept
{}

void Script::Refresh()
{
  

}