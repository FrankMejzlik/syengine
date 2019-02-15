
#include "DirectionalLight_.h"

using namespace SYE;

DirectionalLight::DirectionalLight(
  ComponentManager* pComponentManager,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  glm::vec3 colourVector,
  glm::vec3 lightIntensities,
  glm::vec3 shadowDimensions,
  glm::vec3 lightDirectionVector
) : 
  Light(
    pComponentManager,
    positionVector, rotationVector, scaleVector,
    colourVector,
    lightIntensities,
    shadowDimensions
  ),
  _lightDirectionVector(lightDirectionVector)  
{

  _lightDirectionVector = lightDirectionVector;

  // Calculate projection matrix for this light
  // Directional light uses orthogonal projection
  // TODO: Make modifiable values.
  _lightProjectionMatrix = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
}

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

glm::mat4 DirectionalLight::CalculateLightTransform()
{
  return _lightProjectionMatrix * glm::lookAt(-_lightDirectionVector, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

DirectionalLight::~DirectionalLight()
{}

