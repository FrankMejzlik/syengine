#include "Light_.h"

using namespace SYE;


Light::Light(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef) noexcept :
  Component(
    pOwnerEntity, subModulesConstRef,
    true, true,
    UNDEFINED
  ),
  _pShadowMap(std::move(std::make_unique<ShadowMap>()))
{
  _type = eType::LIGHT;
}

Light::~Light() noexcept
{
  _pShadowMap.reset();
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