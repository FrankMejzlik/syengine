#pragma once

#include "MathLibrary.h"

#include "Component.h"

namespace SYE 
{

class Transform:
  public Component
{
public:
  Transform() = delete;
  Transform(
    Entity* pOwnerEntity, Component* pOwnerComponent,
    eSlotIndex slotIndex = TRANSFORM, Component::eType type = eType::TRANSFORM
  );
  ~Transform() noexcept;

  void SetPosition(Vector3f position) { _position = position; };
  void SetRotation(Vector3f rotation);
  void SetScale(Vector3f scale) { _scale = scale; };
  
  Vector3f GetPosition() const { return _position; };
  const Vector3f& GetPositionConstRef() const { return _position; };
  Vector3f& GetPositionRef() { return _position; };
  Vector3f GetRotation() const { return _rotation; };
  Vector3f GetScale() const  { return _scale; };

  Vector3f GetZDir() const { return _zDir; };
  Vector3f GetYDir() const { return _yDir; };
  Vector3f GetXDir() const { return _xDir; };


protected:
  /** Direction up of virtual world (usually positive Y-axis)*/
  Vector3f _worldUp;

  /** Current Component position */
  Vector3f _position;
  /** Current Component rotation angles (yaw, pitch, roll) in RADIANS */
  Vector3f _rotation;
  /** Current Component scale factors (X, Y, Z) */
  Vector3f _scale;
  
  /** Current direction of local Z-axis (front direction) */
  Vector3f _zDir;
  /** Current direction of local Y-axis */
  Vector3f _yDir;
  /** Current direction of local X-axis */
  Vector3f _xDir;

  
};

}