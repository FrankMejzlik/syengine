#pragma once

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
    Entity* pOwnerEntity, Component* pOwnerComponent,
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