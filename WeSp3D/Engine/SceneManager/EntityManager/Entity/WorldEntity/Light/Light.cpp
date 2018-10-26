#include "Light.h"

using namespace WeSp;


Light::Light(
  std::shared_ptr<ComponentManager> pComponentManager,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  glm::vec3 colourVector,
  glm::vec3 lightIntensities,
  glm::vec3 shadowDimensions
) :
  WorldEntity(pComponentManager, positionVector, rotationVector, scaleVector),
  _colourVector(colourVector), 
  _lightIntensities(lightIntensities), 
  _shadowDimensions(shadowDimensions),
  _pShadowMap(std::make_shared<ShadowMap>())
{
  // Initialize shadow map
  _pShadowMap->Init(_shadowDimensions.x, _shadowDimensions.y);
}

Light::~Light()
{
  _pShadowMap.reset();
}

std::shared_ptr<ShadowMap> Light::GetShadowMap() const
{ 
  return _pShadowMap; 
}