#pragma once

#include <memory>

#include <GL/glew.h>

#pragma warning(push, 1)
#include <glm/gtc/matrix_transform.hpp>
#pragma warning(pop)



#include "ShadowMap.h"
#include "WorldEntity.h"

using namespace SYE;

namespace SYE 
{

class Light:
  public WorldEntity
{
public:
  Light() = delete;

  Light(
    ComponentManager* pComponentManager,
    glm::vec3 positionVector, glm::vec3 rotationVector, glm::vec3 scaleVector,
    glm::vec3 colourVector,
    glm::vec3 lightIntensities,
    glm::vec3 shadowDimensions
  );
  virtual ~Light();

  std::shared_ptr<ShadowMap> GetShadowMap() const;

 
  // TODO: eliminate
  void TogglePoint()
  {
    pointsAreOn = !pointsAreOn;
  }

  void ToggleSpot()
  {
    spotsAreOn = !spotsAreOn;
  }
  bool pointsAreOn;
  bool spotsAreOn;
  // TODO: eliminate

protected:
  // Computed shadow map for this light
  std::shared_ptr<ShadowMap> _pShadowMap;

  // TODO: Make static/dynamic
  bool IsStatic;

  // Colour of light
  glm::vec3 _colourVector;
  // Intensities of specific light parts
  // x: ambient, y: diffuse, z: specular
  glm::vec3 _lightIntensities;
  // Dimensions of shadow map
  // x: width y: height z: unused
  glm::ivec3 _shadowDimensions;
  // Projection matrix for computing shadow map
  glm::mat4 _lightProjectionMatrix;
  // Matrix to transform world to window space from POV of light
  glm::mat4 _lightModelToWindowMatrix;

};

}