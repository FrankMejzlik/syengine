#pragma once

#include <memory>

#include <GL/glew.h>

#pragma warning(push, 1)
#include <glm/gtc/matrix_transform.hpp>
#pragma warning(pop)


#include "MathLibrary.h"
#include "ShadowMap.h"
#include "WorldEntity.h"

using namespace SYE;

namespace SYE 
{

class Light:
  public Component
{
public:
  Light() = delete;
  Light(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef) noexcept;
  virtual ~Light() noexcept;

  glm::vec3 GetColour() const;
  virtual void SetColour(glm::vec3 colourVector);
  glm::vec3 GetIntensities() const;
  virtual void SetInensities(glm::vec3 lightIntensities);
  glm::ivec3 GetShadowDimensions() const;
  virtual void SetShadowDimensions(glm::ivec3 shadowDimensions);

  ShadowMap* GetShadowMap() const;


protected:
  // Computed shadow map for this light
  std::unique_ptr<ShadowMap> _pShadowMap;

  // TODO: Make static/dynamic
  bool _isStatic;

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