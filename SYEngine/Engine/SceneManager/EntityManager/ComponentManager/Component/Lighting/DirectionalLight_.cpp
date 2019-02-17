
#include "DirectionalLight_.h"

using namespace SYE;

DirectionalLight::DirectionalLight(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots) noexcept :
  Light(pOwnerEntity, subModulesConstRef, primaryComponentSlots) 
{
  // Calculate projection matrix for this light
  // Directional light uses orthogonal projection
  // TODO: Make modifiable values.
  _lightProjectionMatrix = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
  _type = eType::DIRECTIONAL_LIGHT;

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


