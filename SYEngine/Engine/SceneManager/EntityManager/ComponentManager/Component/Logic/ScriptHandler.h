#pragma once
#include "Component.h"

namespace SYE 
{

class Scene;
class Script;

class ScriptHandler :
  public Component
{
public:
  ScriptHandler() = delete;
  ScriptHandler(
    Entity* pOwnerEntity, 
    const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, 
    std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots
  ) noexcept;
  virtual ~ScriptHandler() noexcept;

  template <typename ScriptClass>
  ScriptClass* AddScript()
  {
    // Create new Component
    ScriptClass* pScript = _pComponentManager->CreateComponent<ScriptClass>(_pOwnerEntity);

    // Store it to this instance
    _pScript = static_cast<Script*>(pScript);

    return pScript;
  }

  void ClearScript();

  void TriggerOnInitializeScene();
  void TriggerOnProcessFrame(dfloat deltaTime, Scene* pScene);


  // Attributes
private:
  Script* _pScript;

};

}