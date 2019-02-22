#include "Light.h"
#include "Transform.h"
using namespace SYE;


Light::Light(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots) noexcept :
  Component(
    pOwnerEntity, subModulesConstRef, primaryComponentSlots,
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

void Light::Refresh()
{
  /**
  * Update all quick refs to sibling Components
  */

  // Update Transform quick ref
  if (!_primaryComponentSlots[COMPONENT_TRANSFORM_SLOT].empty())
  {
    _pTransform = static_cast<Transform*>(_primaryComponentSlots[COMPONENT_TRANSFORM_SLOT].begin()->second);
  }

}

const Vector3f& Light::GetPositionConstRef() const 
{ 
  return _pTransform->GetPositionConstRef(); 
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