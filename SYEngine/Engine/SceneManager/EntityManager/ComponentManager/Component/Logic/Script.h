#pragma once

// Shortcuts to parent quick refs
#define GET_TRANSFORM _pParent->GetTransformPtr()


#include "Component.h"

namespace SYE 
{

class Scene;
class Transform;
class ScriptHandler;

class Script :
  public Component
{
  // Methods
public:
  Script() = delete;
  Script(
    Entity* pOwnerEntity, 
    const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, 
    std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots,
    eSlotIndex slotIndex = UNDEFINED, Component::eType type = eType::SCRIPT
  );
  virtual ~Script() noexcept;

  virtual void OnInitializeScene() = 0;
  virtual void OnProcessFrame(dfloat deltaTime, Scene* pScene) = 0;

  void SetParentPtr(ScriptHandler* pParent) { _pParent = pParent; }

  // Attributes
protected:
  ScriptHandler* _pParent;

};


}