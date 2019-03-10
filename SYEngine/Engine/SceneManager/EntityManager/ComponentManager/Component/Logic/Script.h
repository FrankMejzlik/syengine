#pragma once

#include "Component.h"
#include "PhysicsBody.h"

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

  /*!
   * This function is called whenever some PhysicsBody on Entity we're attached to is in collision
   * 
   * \param collision Reference to structure containing all needed data about this collision.
   */
  virtual void OnCollision(const PhysicsBody::Collision& collision);
  virtual void OnInitializeScene() = 0;
  virtual void OnProcessFrame(dfloat deltaTime, Scene* pScene) = 0;

  void SetParentPtr(ScriptHandler* pParent) { _pParent = pParent; }

  // Attributes
protected:
  ScriptHandler* _pParent;

};


}