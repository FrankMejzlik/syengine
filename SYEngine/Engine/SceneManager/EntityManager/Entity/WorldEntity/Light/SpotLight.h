#pragma once


#include "PointLight.h"

using namespace SYE;

namespace SYE 
{

class SpotLight :
  public PointLight
{
public:
  SpotLight() = delete;
  SpotLight(
    std::shared_ptr<ComponentManager> pComponentManager,
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    glm::vec3 colourVector,
    glm::vec3 lightIntensities,
    glm::vec3 shadowDimensions,
    glm::vec2 planeDimensions,
    glm::vec3 coefficients,
    glm::vec3 lightDirection,
    GLfloat coneAngle
  );
  ~SpotLight();

  void UseLight(
    GLuint ambientIntensityLocation,
    GLuint ambientColourLocation,
    GLuint diffuseIntensityLocation,
    GLuint positionLocation,
    GLuint directionLocation,
    GLuint constantLocation,
    GLuint linearLocation,
    GLuint exponentLocation,
    GLuint edgeLocation
  );

  void SetFlash(glm::vec3 pos, glm::vec3 dir);

private:
  glm::vec3 _lightDirection;

  GLfloat _coneAngle, _processedConeAngle;
};

}