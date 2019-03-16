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
#include <GL/glew.h>

#pragma warning(push, 1)
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#pragma warning(pop)

#include "Component.h"


//////////////////

#include "IerrorLogging.h"
#include "IGuidCounted.h"

using namespace SYE;

namespace SYE 
{
class NewShader:
  public IErrorLogging, public IGuidCounted
{
  // Structs
public:
  enum eUniforms
  {
    cMVPTransformMatrix,
    cEyePosition,
    cEyeDirection,
    cSpecularIntensity,
    cShininessIntensity,
    cDiffuseTexture,
    cNormalMapTexture,
    cDirectionalShadowMap
  };

  // Methods
public:
  NewShader() = delete;
  NewShader(
    std::vector<NewShader::eUniforms> _requiredUniforms,
    std::vector<NewShader::eUniforms> _optionalUniforms,
    std::string_view vsFilepath, 
    std::string_view fsFilepath,
    std::string_view tsFilepath  = std::string_view(),
    std::string_view gsFilepath  = std::string_view()
  );
  ~NewShader() noexcept;
  

  bool UseShader();
  void ClearShader();

  GLuint GetShaderId();

  //! Matrix getters
  GLuint GetMVPTransformMatrixUL() const;

  GLuint GetEyePositionUL() const;
  GLuint GetEyeDirectionUL() const;

  GLuint GetSpecularIntensityUL() const;
  GLuint GetShininessIntentistyUL() const;
  
  //! Texture getters
  GLuint GetDiffuseTextureUL() const;
  GLuint GetNormalMapTextureUL() const;
  GLuint GetDirectionalLightShadowMapUL() const;

  GLuint GetNearPlaneLocationUL() const;
  GLuint GetFarPlaneLocationUL() const;

  
  //! Matrix setters
  void SetMVPTransformMatrix(const glm::mat4& transformMatrix) const;

  void SetEyePosition(const glm::vec3& position) const;
  void SetEyeDirection(const glm::vec3& direction) const;

  void SetSpecularIntensity(dfloat value) const;
  void SetShininessIntentisty(size_t value) const;

  //! Texture setters
  void SetDiffuseTexture(GLuint textureUnit) const;
  void SetNormalMapTexture(GLuint textureUnit) const;
  void SetDirectionalShadowMap(GLuint textureUnit) const;
  

  const std::vector<NewShader::eUniforms>& GetRequiredUniformsConstRef() const;
  const std::vector<NewShader::eUniforms>& GetOptionalUniforms() const;

  bool LoadSelfWithUniformsFrom(Camera* pCamera, MeshRenderer* pMeshRenderer);
  
private:
  bool CompileProgram();
  void UpdateUnirofmLocations();
  bool Validate();

  bool CreateShader(
    std::string_view vsFilepath, 
    std::string_view fsFilepath,
    std::string_view tsFilepath,
    std::string_view gsFilepath
  );


  void CreateSpecificShader(GLuint theProgram, std::string_view shaderCode, GLenum shaderType);

  bool LoadUniformFrom(Camera* pCamera, MeshRenderer* pMeshRenderer, eUniforms uniformType);



  // Attributes
private:
  //! List of required uniforms for rendering
  std::vector<NewShader::eUniforms> _requiredUniforms;

  //! List of oprional uniforms for rendering
  std::vector<NewShader::eUniforms> _optionalUniforms;

  //! Shader ID of normal Shader
  GLuint _shaderId;
  
  GLuint _ulMVPTransformMatrix;

  GLuint _ulEyePosition;
  GLuint _ulEyeDirection;

  GLuint _ulSpecularIntensity;
  GLuint _ulShininessIntentisty;

  GLuint _ulDiffuseTexture;
  GLuint _ulNormalMapTexture;

  GLuint _ulDirectionalLightShadowMap;

  GLuint _ulNearPlane;
  GLuint _ulFarPlane;

};




class Shader
{
public:
  Shader() = delete;

  Shader(
    Entity* pOwnerEntity, Component* pOwnerComponent,
    Component::eSlotIndex slotIndex = Component::UNDEFINED, Component::eType type = Component::eType::SHADER
  );
  
  void SetupDirectionalLight(DirectionalLight* dLight);
  void dc_SetDirectionalLight(DirectionalLight* dLight);
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

  void dc_CompileProgram();

  void CompileProgram();

  void CompileShader(const char* vertexCode, const char* fragmentCode);
  void CompileShader(const char* vertexCode, const char* geometryCode, const char* fragmentCode);
  void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

}