#include "Light.h"

using namespace SYE;


_Light::_Light(
  ComponentManager* pComponentManager,
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
  _pShadowMap->Init(
    static_cast<unsigned int>(_shadowDimensions.x), 
    static_cast<unsigned int>(_shadowDimensions.y)
  );
}

_Light::~_Light()
{
  _pShadowMap.reset();
}

std::shared_ptr<ShadowMap> _Light::GetShadowMap() const
{ 
  return _pShadowMap; 
}