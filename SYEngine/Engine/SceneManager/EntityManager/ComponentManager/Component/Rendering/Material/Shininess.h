#pragma once

#include "Component.h"

namespace SYE
{

class Entity;

/**
 * Describes how specular lights behave on surface
 *
 * @see   class Material
 */
class Shininess :
  public Component
{
public:
  Shininess() = delete;

  /**
   * Default constructor
   *
   *  EXAMPLE VALUES:
   *    shiny: 1.0f, 512
   *    dull: 0.3f  4
   */
  Shininess(
    Entity* pOwnerEntity, Component* pOwnerComponent,
    eSlotIndex slotIndex = UNDEFINED, Component::eType type = eType::SHININESS
  );

  void SetSpecularIntensity(dfloat newValue);
  void SetShininessIntensity(dfloat newValue);
  dfloat GetSpecularIntensity() const;
  dfloat GetShininessIntensity() const;

private:
  dfloat _specularIntensity;
  dfloat _shininessIntensity;


};

}