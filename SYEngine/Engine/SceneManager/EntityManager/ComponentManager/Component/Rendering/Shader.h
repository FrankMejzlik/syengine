#pragma once

#include <unordered_map>

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionalLight.h"

#include <GLFW/glfw3.h>
#include <GL\glew.h>

#pragma warning(push, 1)
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#pragma warning(pop)


#include "Component.h"

using namespace SYE;

namespace SYE 
{

class Shader//:
  //public Component
{
public:
  Shader() = delete;

  Shader(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots);
  

  void SetDirectionalLight(DirectionalLight* dLight);
  void SetPointLights(
    const std::map<size_t, Component*>& pointLights,
    size_t textureUnit,
    size_t offset
  );
  void SetSpotLights(
    const std::map<size_t, Component*>& spotLights,
    size_t textureUnit,
    size_t offset
  );

  void SetIsSkeletonAnimated(int newValue)
  {
    // Set to skeleton animated model.
    glUniform1i(_ul_bIsSkeletonAnimated, (GLint)newValue);

    const GLubyte*  stdee;
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
      // Process/log the error.
      stdee = gluErrorString(err);
      printf("ERROR GL: %s", stdee);
    }

  }

  void CreateFromString(const char* vertexCode, const char* fragmentCode);
  void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);
  void CreateFromFiles(const char* vertexLocation, const char* geometryLocation, const char* fragmentLocation);

  GLuint GetShaderID();

  void Validate();

  std::string ReadFile(const char* fileLocation);

  GLuint GetUniformLocation_bIsSkeletonAnimated()
  {
    return _ul_bIsSkeletonAnimated;
  }

  GLuint GetProjectionLocation();
  GLuint GetModelLocation();
  GLuint GetViewLocation();
  GLuint GetAmbientIntensityLocation();
  GLuint GetAmbientColourLocation();
  GLuint GetDiffuseIntensityLocation();
  GLuint GetDirectionLocation();
  GLuint GetSpecularIntensityLocation();
  GLuint GetShininessLocation();
  GLuint GetEyePosition();

  GLuint GetOmniLightPosLocation();
  GLuint GetFarPlaneLocation();

  void SetTexture(GLuint textureUnit);
  void SetDirectionalShadowMap(GLuint textureUnit);

  void SetDirectionalLightTransform(glm::mat4* lTransform);
  void SetOmniLightMatrices(std::vector<glm::mat4> lightMatrices);


  void UseShader();
  void ClearShader();
  
  ~Shader();

private:
  int pointLightCount;
  int spotLightCount;

  GLuint _ul_bIsSkeletonAnimated;

  GLuint shaderID, uniformProjection, uniformModel, uniformView, uniformEyePosition;
  
  GLuint uniformSpecularIntensity, uniformShininess;
  GLuint uniformDirectionalLightTransform, uniformDirectionalShadowMap, uniformTexture;
  GLuint uniformOmniLightPos, uniformFarPlane;

  GLuint uniformLightMatrices[6];

  struct 
  {
    GLuint uniformColour;
    GLuint uniformAmbientIntensity;
    GLuint uniformDiffuseIntensity;

    GLuint uniformDirection;
  } uniformDirectionalLight;

  GLint uniformPointLightCount;
  GLint uniformSpotLightCount;

  struct 
  {
    GLuint uniformColour;
    GLuint uniformAmbientIntensity;
    GLuint uniformDiffuseIntensity;

    GLuint uniformPosition;
    GLuint uniformConstant;
    GLuint uniformLinear;
    GLuint uniformExponent;
  } uniformPointLight[MAX_POINT_LIGHTS];

  struct
  {
    GLuint uniformColour;
    GLuint uniformAmbientIntensity;
    GLuint uniformDiffuseIntensity;

    GLuint uniformPosition;
    GLuint uniformConstant;
    GLuint uniformLinear;
    GLuint uniformExponent;

    GLuint uniformDirection;
    GLuint uniformEdge;

  } uniformSpotLight[MAX_SPOT_LIGHTS];


  struct
  {
    GLuint uniformShadowMap;
    GLuint uniformFarPlane;
  } uniformOmniShadowMap[MAX_SPOT_LIGHTS + MAX_POINT_LIGHTS];

  void CompileProgram();
  void CompileShader(const char* vertexCode, const char* fragmentCode);
  void CompileShader(const char* vertexCode, const char* geometryCode, const char* fragmentCode);
  void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

}