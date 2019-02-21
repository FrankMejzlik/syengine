#pragma once

#include "Component.h"

namespace SYE 
{

class Scene;
class Transform;

class Script :
  public Component
{
  // Methods
public:
  Script() = delete;
  Script(
    Entity* pOwnerEntity, 
    const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, 
    std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots
  ) noexcept;
  virtual ~Script() noexcept;

  virtual void Refresh();

  virtual void OnInitializeScene() = 0;
  virtual void OnProcessFrame(dfloat deltaTime, Scene* pScene) = 0;

  // Attributes
protected:
  // Quick refs
  Transform* _pTransform;

};


}