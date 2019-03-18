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
  
  /*!
   * This function is called just before Scene initialization.
   * 
   */
  virtual void OnInitializeScene() = 0;

  /*!
   * This method is called every frame to execute this script.
   * 
   * \param Time since las frame.
   * \param Pointer to Scene instance this is in.
   */
  virtual void OnProcessFrame(dfloat deltaTime, Scene* pScene) = 0;

  void SetParentPtr(ScriptHandler* pParent) { _pParent = pParent; }

  // Attributes
protected:
  ScriptHandler* _pParent;

};


}