#pragma once

#include "CommonValues.h"
#include "MathLibrary.h"

#include "Component.h"

namespace SYE 
{

class Transform:
  public Component
{
public:
  Transform() = delete;
  Transform(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef) noexcept;
  Transform(
    Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef,
    Vector3f position,
    Vector3f rotation,
    Vector3f scale
  ) noexcept;
  ~Transform() noexcept;

  void SetPosition(Vector3f position) { _position = position; };
  void SetRotation(Vector3f rotation) { _rotation = rotation; };
  void SetScale(Vector3f scale) { _scale = scale; };
  Vector3f GetPosition() const { return _position; };
  Vector3f GetRotation() const { return _rotation; };
  Vector3f GetScale() const  { return _scale; };

protected:
  Vector3f _position;
  Vector3f _rotation;
  Vector3f _scale;

  
};

}