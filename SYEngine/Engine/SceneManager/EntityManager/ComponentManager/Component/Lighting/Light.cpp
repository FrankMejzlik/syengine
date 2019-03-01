#include "Light.h"
#include "Transform.h"
using namespace SYE;


Light::Light(
  Entity* pOwnerEntity, Component* pOwnerComponent,
  eSlotIndex slotIndex, Component::eType type
) :
  Component(
    pOwnerEntity, pOwnerComponent,
    true, true,
    slotIndex , type 
  ),
  _pShadowMap(std::move(std::make_unique<ShadowMap>()))
{
}

Light::~Light() noexcept
{
  _pShadowMap.reset();
}

const Vector3f& Light::GetPositionConstRef() const 
{ 
  return GetTransformPtr()->GetPositionConstRef(); 
}

glm::vec3 Light::GetColour() const
{
  return _colourVector;
}

void Light::SetColour(glm::vec3 colourVector)
{
  _colourVector = colourVector;
}

glm::vec3 Light::GetIntensities() const
{
  return _lightIntensities;
}

void Light::SetInensities(glm::vec3 lightIntensities)
{
  _lightIntensities = lightIntensities;
}


glm::ivec3 Light::GetShadowDimensions() const
{
  return _shadowDimensions;
}

void Light::SetShadowDimensions(glm::ivec3 shadowDimensions)
{
  _shadowDimensions = shadowDimensions;

  // Initialize shadow map
  _pShadowMap->Init(
    static_cast<unsigned int>(_shadowDimensions.x),
    static_cast<unsigned int>(_shadowDimensions.y)
  );
}

ShadowMap* Light::GetShadowMap() const
{ 
  return _pShadowMap.get(); 
}