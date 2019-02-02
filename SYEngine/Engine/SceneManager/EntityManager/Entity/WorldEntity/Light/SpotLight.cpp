#include "SpotLight.h"

using namespace SYE;


SpotLight::SpotLight(
  ComponentManager* pComponentManager,
  glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
  glm::vec3 colourVector,
  glm::vec3 lightIntensities,
  glm::vec3 shadowDimensions,
  glm::vec2 planeDimensions,
  glm::vec3 coefficients,
  glm::vec3 lightDirection,
  GLfloat coneAngle
):
  PointLight(
    pComponentManager,
    positionVector, rotationVector, scaleVector,
    colourVector,
    lightIntensities,
    shadowDimensions,
    planeDimensions,
    coefficients
  ),
  _lightDirection(glm::normalize(lightDirection)),
  _coneAngle(coneAngle),
  _processedConeAngle(cosf(glm::radians(coneAngle)))
{}


SpotLight::~SpotLight()
{}

void SpotLight::UseLight(
  GLuint ambientIntensityLocation, 
  GLuint ambientColourLocation, 
  GLuint diffuseIntensityLocation, 
  GLuint positionLocation, 
  GLuint directionLocation, 
  GLuint constantLocation, 
  GLuint linearLocation, 
  GLuint exponentLocation, 
  GLuint edgeLocation
)
{
  glUniform3f(ambientColourLocation, _colourVector.x, _colourVector.y, _colourVector.z);
  glUniform1f(ambientIntensityLocation, _lightIntensities.x);
  glUniform1f(diffuseIntensityLocation, _lightIntensities.y);


  glUniform3f(positionLocation, _positionVector.x, _positionVector.y, _positionVector.z);

  glUniform1f(constantLocation, _constant);
  glUniform1f(linearLocation, _linear);
  glUniform1f(exponentLocation, _exponent);

  glUniform3f(directionLocation, _lightDirection.x, _lightDirection.y, _lightDirection.z);
  glUniform1f(edgeLocation, _processedConeAngle);
}

void SpotLight::SetFlash(glm::vec3 pos, glm::vec3 dir)
{
  _positionVector = pos;
  _lightDirection = dir;
  return;
}

