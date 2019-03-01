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
    Entity* pOwnerEntity, 
    const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, 
    std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots,
    eSlotIndex slotIndex = SCRIPT_HANDLER, Component::eType type = eType::SCRIPT_HANDLER
  );
  virtual ~ScriptHandler() noexcept;

  void Refresh();

  template <typename ScriptClass>
  ScriptClass* AddScript()
  {
    // Create new Component
    ScriptClass* pScript = _pComponentManager->CreateComponent<ScriptClass>(_pOwnerEntity, this);

    // Setup child Script ptr to self
    pScript->SetParentPtr(this);

    // Store it to this instance
    _pScript = static_cast<Script*>(pScript);

    return pScript;
  }

  void ClearScript();

  void TriggerOnInitializeScene();
  void TriggerOnProcessFrame(dfloat deltaTime, Scene* pScene);

  Transform* GetTransformPtr();

  // Attributes
private:
  Script* _pScript;

  // Quick refs
  Transform* _pTransform;

};

}