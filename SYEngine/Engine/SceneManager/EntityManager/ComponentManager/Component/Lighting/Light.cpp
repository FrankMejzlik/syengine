#include "Light.h"
#include "Transform.h"

#include "Texture.h"
#include "Scene.h"
#include "ComponentManager.h"
#include "Entity.h"


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
#if !NEW_SHADOW_MAPPING_IMPLEMENTED
  dc_pShadowMap(std::move(std::make_unique<ShadowMap>())),
#endif
  _pShadowInfo(nullptr)
{
  // xoxo
  // Create shadow map
  _pShadowMap = GetComponentManagerPtr()->CreateComponent<Texture>(pOwnerEntity->GetOwnerScenePtr()->GetRootEntity());
  _pShadowMap->LoadDepthTexture(1024ULL, 1024ULL);

}

Light::~Light() noexcept
{
  dc_pShadowMap.reset();
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
  dc_pShadowMap->Init(
    static_cast<unsigned int>(_shadowDimensions.x),
    static_cast<unsigned int>(_shadowDimensions.y)
  );
}

ShadowMap* Light::dc_GetShadowMap() const
{ 
  return dc_pShadowMap.get(); 
}