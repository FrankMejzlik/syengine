#pragma once

#include "Light.h"

using namespace SYE;

namespace SYE 
{

/**
 * Light that is in infinite distance. It has direction.
 */
class DirectionalLight :
  public Light
{
public:
  DirectionalLight() = delete;
  DirectionalLight(
    std::shared_ptr<ComponentManager> pComponentManager,
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    glm::vec3 colourVector,
    glm::vec3 lightIntensities,
    glm::vec3 shadowDimensions,
    glm::vec3 lightDirectionVector
  );
  virtual ~DirectionalLight();

  void UseLight(
    GLuint ambientIntensityLocation, 
    GLuint ambientColourLocation,
    GLuint diffuseIntensityLocation, 
    GLuint directionLocation
  );

  // Calculates matrix to transform world to "POV of this light"
  glm::mat4 CalculateLightTransform();

protected:
  // Direction of light
  glm::vec3 _lightDirectionVector;
};

}