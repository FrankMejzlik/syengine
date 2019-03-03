#pragma once
#include "Component.h"
#include "ComponentManager.h"

namespace SYE 
{

class Scene;
class Script;
class Transform;

class ScriptHandler :
  public Component
{
public:
  ScriptHandler() = delete;
  ScriptHandler(
    Entity* pOwnerEntity, Component* pOwnerComponent,
    eSlotIndex slotIndex = SCRIPT_HANDLER, Component::eType type = eType::SCRIPT_HANDLER
  );
  virtual ~ScriptHandler() noexcept;

  template <typename ScriptClass>
  ScriptClass* AddScript()
  {
    // Create new Component
    ScriptClass* pScript = GetComponentManagerPtr()->CreateComponent<ScriptClass>(_pOwnerEntity, this);

    // Setup child Script ptr to self
    pScript->SetParentPtr(this);

    // Store it to this instance
    _pScript = static_cast<Script*>(pScript);

    return pScript;
  }

  Script* GetAttachedScriptPtr() const
  {
    return _pScript;
  }

  void ClearScript();

  void TriggerOnInitializeScene();
  void TriggerOnProcessFrame(dfloat deltaTime, Scene* pScene);

  // Attributes
private:
  Script* _pScript;


};

}