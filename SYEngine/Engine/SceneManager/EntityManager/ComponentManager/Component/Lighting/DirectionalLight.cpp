
#include "DirectionalLight.h"

using namespace SYE;

DirectionalLight::DirectionalLight(
  Entity* pOwnerEntity, Component* pOwnerComponent,
  eSlotIndex slotIndex, Component::eType type
) :
  Light(pOwnerEntity, pOwnerComponent, slotIndex, type) 
{
#if !NEW_SHADOW_MAPPING_IMPLEMENTED
  // Calculate projection matrix for this light
  // Directional light uses orthogonal projection
  // TODO: Make modifiable values.
  _lightProjectionMatrix = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, LIGHTS_NEAR_PLANE, LIGHTS_FAR_PLANE);
#endif

  // Instantiate ShadowInfo for this light
  SetShadowInfo(std::make_unique<ShadowInfo>(Matrix4f(glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, LIGHTS_NEAR_PLANE, LIGHTS_FAR_PLANE))));
}

DirectionalLight::~DirectionalLight() noexcept
{}

void DirectionalLight::UseLight(
  GLuint ambientIntensityLocation,
  GLuint ambientColourLocation,
  GLuint diffuseIntensityLocation,
  GLuint directionLocation
)
{
  // Setup uniforms in shader
  glUniform3f(ambientColourLocation, _colourVector.x, _colourVector.y, _colourVector.z);
  glUniform1f(ambientIntensityLocation, _lightIntensities.x);
  glUniform3f(directionLocation, _lightDirectionVector.x, _lightDirectionVector.y, _lightDirectionVector.z);
  glUniform1f(diffuseIntensityLocation, _lightIntensities.y);
}

glm::mat4 DirectionalLight::CalculateLightTransformMatrix()
{
  return _lightProjectionMatrix * glm::lookAt(-_lightDirectionVector, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}


