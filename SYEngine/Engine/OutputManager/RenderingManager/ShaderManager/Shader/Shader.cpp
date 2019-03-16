#include "Shader.h"

#include "Component.h"
#include "Utils.h"

using namespace SYE;


NewShader::NewShader(
  std::string_view vsFilepath,
  std::string_view fsFilepath,
  std::string_view tsFilepath,
  std::string_view gsFilepath
):
  _shaderId(0),
  _ulMVPTransformMatrix(0),
  _ulEyePosition(0),
  _ulSpecularIntensity(0),
  _ulShininessIntentisty(0),
  _ulDiffuseTexture(0),
  _ulNormalMapTexture(0),
  _ulDirectionalLightShadowMap(0),
  _ulNearPlane(0),
  _ulFarPlane(0)
{

  // Compile Shaders on GPU
  bool result = CreateShader(vsFilepath, fsFilepath, tsFilepath, gsFilepath);
  if (!result)
  {
    PUSH_ENGINE_ERROR(
      eEngineError::FailedToCreateShader,
      std::string("Failed to load to create Shader from files: ") + vsFilepath.data() + fsFilepath.data(),
      ""
    );
  }
}

NewShader::~NewShader()
{
  // Delete shader
  ClearShader();
}

GLuint NewShader::GetShaderId()
{
  return _shaderId;
}


bool NewShader::Validate()
{
  GLint result = 0;
  GLchar eLog[1024] = { 0 };

  // Validate shader
  glValidateProgram(_shaderId);
  glGetProgramiv(_shaderId, GL_VALIDATE_STATUS, &result);
  if (!result)
  {
    glGetProgramInfoLog(_shaderId, sizeof(eLog), NULL, eLog);
    printf("Error validating program: '%s'\n", eLog);

    PUSH_ENGINE_ERROR(
      eEngineError::ValidatingShaderFailed, 
      std::string("Failed to validate Shader with ID ") + std::to_string(_shaderId),
      ""
    );

    // Set to warning state
    SetState(eState::cWarning);

    return false;
  }

  return true;
}


bool NewShader::UseShader()
{
  // If validation fails or is in Error state
  if (!Validate() || GetState() == eState::cError)
  {
    PUSH_ENGINE_ERROR(
      eEngineError::UseShaderFailed,
      std::string("Failed to use Shader with ID ") + std::to_string(_shaderId) + std::string(" beacause validation failed or is in error state."),
      ""
    );

    return false;
  }

  glUseProgram(_shaderId);

  return true;
}

void NewShader::ClearShader()
{
  // If shader allocated
  if (_shaderId != 0)
  {
    // Delete it
    glDeleteProgram(_shaderId);
    _shaderId = 0;
  }

  // Reset uniform locations
  _ulMVPTransformMatrix = 0;

  _ulEyePosition = 0;
  _ulEyeDirection = 0;

  _ulSpecularIntensity = 0;
  _ulShininessIntentisty = 0;

  _ulDiffuseTexture = 0;
  _ulNormalMapTexture = 0;

  _ulDirectionalLightShadowMap = 0;

  _ulNearPlane = 0;
  _ulFarPlane = 0;
}



bool NewShader::CreateShader(
  std::string_view vsFilepath, 
  std::string_view fsFilepath,
  std::string_view tsFilepath,
  std::string_view gsFilepath
)
{
  // Create new shader program
  _shaderId = glCreateProgram();

  // If error
  if (!_shaderId)
  {
    PUSH_ENGINE_ERROR(
      eEngineError::FailedToGenerateShaderProgram,
      std::string("Failed to create Shader in OpenGL. Shader with vs in ") + vsFilepath.data(),
      ""
    );
    SetState(eState::cError);

    return false;
  }

  // Create Vertex Shader
  CreateSpecificShader(_shaderId, Utils::ReadTextFile(vsFilepath), GL_VERTEX_SHADER);

  // Create Fragment Shader
  CreateSpecificShader(_shaderId, Utils::ReadTextFile(fsFilepath), GL_FRAGMENT_SHADER);

  // If Tessellation Shader provided
  if (!tsFilepath.empty())
  {
    CreateSpecificShader(_shaderId, Utils::ReadTextFile(tsFilepath), GL_TESS_CONTROL_SHADER);
  }

  // If Geometry Shader provided
  if (!tsFilepath.empty())
  {
    CreateSpecificShader(_shaderId, Utils::ReadTextFile(gsFilepath), GL_GEOMETRY_SHADER);
  }
  
  // Compile whole shader
  if (!CompileProgram())
  {
    PUSH_ENGINE_ERROR(
      eEngineError::FailedToCreateShader,
      std::string("Failed to create Shader with ID") + std::to_string(GetGuid()),
      std::string("REASON: CompileProgram() failed.")
    );
    SetState(eState::cError);

    return false;
  }

  // Update uniform locations
  UpdateUnirofmLocations();

  return true;
}

void NewShader::UpdateUnirofmLocations()
{
  _ulMVPTransformMatrix = glGetUniformLocation(_shaderId, UNUFORM_NAME_MVP_TRANSFORM_MATRIX);

  _ulEyePosition = glGetUniformLocation(_shaderId, UNUFORM_NAME_EYE_POSITION);
  _ulEyeDirection = glGetUniformLocation(_shaderId, UNUFORM_NAME_EYE_DIRECTION);

  _ulSpecularIntensity = glGetUniformLocation(_shaderId, UNUFORM_NAME_SPECULAR_INTENSITY);
  _ulShininessIntentisty = glGetUniformLocation(_shaderId, UNUFORM_NAME_SHININESS_INTENSITY);

  _ulDiffuseTexture = glGetUniformLocation(_shaderId, UNUFORM_NAME_DIFFUSE_TEXTURE);
  _ulNormalMapTexture = glGetUniformLocation(_shaderId, UNUFORM_NAME_NORMAL_MAP_TEXTUE);

  //! \todo Make for multiple directional lights
  _ulDirectionalLightShadowMap = glGetUniformLocation(_shaderId, UNUFORM_NAME_NORMAL_MAP_TEXTUE);

  _ulNearPlane = glGetUniformLocation(_shaderId, UNUFORM_NAME_NEAR_PLANE);
  _ulFarPlane = glGetUniformLocation(_shaderId, UNUFORM_NAME_FAR_PLANE);


  // struct exmaple:
  //uniformDirectionalLight.uniformColour = glGetUniformLocation(shaderID, "directionalLight.base.colour");
  //uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.base.ambientIntensity");
  //uniformDirectionalLight.uniformDirection = glGetUniformLocation(shaderID, "directionalLight.direction");
  //uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.base.diffuseIntensity");
  //uniformSpecularIntensity = glGetUniformLocation(shaderID, "material.specularIntensity");
  //uniformShininess = glGetUniformLocation(shaderID, "material.shininess");
  //uniformEyePosition = glGetUniformLocation(shaderID, "eyePosition");

}

bool NewShader::CompileProgram()
{
  GLint result = 0;
  GLchar errorDescription[1024] = { 0 };

  // Link shader
  glLinkProgram(_shaderId);
  glGetProgramiv(_shaderId, GL_LINK_STATUS, &result);
  
  // If error
  if (!result)
  {
    // Get error description
    glGetProgramInfoLog(_shaderId, sizeof(errorDescription), NULL, errorDescription);
    
    PUSH_ENGINE_ERROR(
      eEngineError::FailedToLinkShaderProgram,
      std::string("Failed to link Shader with ID ") + std::to_string(_shaderId),
      std::string(errorDescription)
    );

    return false;
  }

  // Get all possible uniform location handle IDs
  UpdateUnirofmLocations();

  // Compilation successful
  return true;
}


void NewShader::CreateSpecificShader(GLuint shaderProgram, std::string_view shaderCode, GLenum shaderType)
{
  // Create shader object to be attached to ShaderProgram
  GLuint shaderObject = glCreateShader(shaderType);

  const GLchar* glShaderCode = shaderCode.data();
  GLint codeLength = static_cast<GLuint>(shaderCode.size());

  glShaderSource(shaderObject, 1, &glShaderCode, &codeLength);
  glCompileShader(shaderObject);

  GLint result = 0;
  GLchar errorDescription[1024] = { 0 };

  glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &result);
  if (!result)
  {
    // Get error description
    glGetShaderInfoLog(shaderObject, sizeof(errorDescription), NULL, errorDescription);

    PUSH_ENGINE_ERROR(
      eEngineError::FailedToCompileShaderProgram,
      std::string("Failed to compile Shader with ID ") + std::to_string(_shaderId),
      std::string(errorDescription)
    );

    return;
  }

  // Attach this shader code with this ShaderProgram
  glAttachShader(shaderProgram, shaderObject);
}




GLuint NewShader::GetMVPTransformMatrixUL() const
{
  return _ulMVPTransformMatrix;
}

GLuint NewShader::GetEyePositionUL() const
{
  return _ulEyePosition;
}

GLuint NewShader::GetEyeDirectionUL() const
{
  return _ulEyeDirection;
}

GLuint NewShader::GetSpecularIntensityUL() const
{
  return _ulSpecularIntensity;
}

GLuint NewShader::GetShininessIntentistyUL() const
{
  return _ulShininessIntentisty;
}

GLuint NewShader::GetDiffuseTextureUL() const
{
  return _ulDiffuseTexture;
}

GLuint NewShader::GetNormalMapTextureUL() const
{
  return _ulNormalMapTexture;
}


GLuint NewShader::GetDirectionalLightShadowMapUL() const
{
  return _ulDirectionalLightShadowMap;
}

GLuint NewShader::GetNearPlaneLocationUL() const
{
  return _ulNearPlane;
}

GLuint NewShader::GetFarPlaneLocationUL() const
{
  return _ulFarPlane;
}

void NewShader::SetDiffuseTexture(GLuint textureUnit) const
{
  glUniform1i(_ulDiffuseTexture, textureUnit);
}

void NewShader::SetNormalMapTexture(GLuint textureUnit) const
{
  glUniform1i(_ulNormalMapTexture, textureUnit);
}

void NewShader::SetDirectionalShadowMap(GLuint textureUnit) const
{
  glUniform1i(_ulDirectionalLightShadowMap, textureUnit);
}

void NewShader::SetMVPTransformMatrix(const glm::mat4& transformMatrix) const
{
  glUniformMatrix4fv(_ulMVPTransformMatrix, 1, GL_FALSE, glm::value_ptr(transformMatrix));
}

void NewShader::SetEyePosition(const glm::vec3& position) const
{
  glUniform3f(_ulEyePosition,  position.x, position.y, position.z);
}

void NewShader::SetEyeDirection(const glm::vec3& direction) const
{
  glUniform3f(_ulEyeDirection,  direction.x, direction.y, direction.z);
}

void NewShader::SetSpecularIntensity(dfloat value) const
{
  glUniform1f(_ulSpecularIntensity, value);
}

void NewShader::SetShininessIntentisty(size_t value) const
{
  glUniform1i(_ulShininessIntentisty, static_cast<GLint>(value));
}






///////////////////////////////
// Old shader implementation
///////////////////////////////

Shader::Shader(
  Entity* pOwnerEntity, Component* pOwnerComponent,
  Component::eSlotIndex slotIndex, Component::eType type
):
  //Component(pOwnerEntity, pOwnerComponent, primaryComponentSlots, true),
  _ul_bIsSkeletonAnimated(0),
  shaderID(0), 
  uniformModel(0), 
  uniformProjection(0), 

  pointLightCount(0),
  spotLightCount(0)
{
  UNREFERENCED_PARAMETER(pOwnerComponent);
  UNREFERENCED_PARAMETER(pOwnerEntity);
  UNREFERENCED_PARAMETER(slotIndex);
  UNREFERENCED_PARAMETER(type);

}

GLuint Shader::GetShaderID()
{
  return shaderID;
}


void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode)
{
  CompileShader(vertexCode, fragmentCode);
}

void Shader::CreateFromFiles(const char* vertexLocation, const char* fragmentLocation)
{
  std::string vertexString = ReadFile(vertexLocation);
  std::string fragmentString = ReadFile(fragmentLocation);
  const char* vertexCode = vertexString.c_str();
  const char* fragmentCode = fragmentString.c_str();

  CompileShader(vertexCode, fragmentCode);
}

void Shader::CreateFromFiles(const char * vertexLocation, const char * geometryLocation, const char * fragmentLocation)
{
  std::string vertexString = ReadFile(vertexLocation);
  std::string fragmentString = ReadFile(fragmentLocation);
  std::string geometryString = ReadFile(geometryLocation);
  const char* vertexCode = vertexString.c_str();
  const char* fragmentCode = fragmentString.c_str();
  const char* geometryCode = geometryString.c_str();

  CompileShader(vertexCode, geometryCode, fragmentCode);
}

void Shader::Validate()
{
  GLint result = 0;
  GLchar eLog[1024] = { 0 };

  // Validate shader
  glValidateProgram(shaderID);
  glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
  if (!result)
  {
    glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
    printf("Error validating program: '%s'\n", eLog);
    return;
  }
}

std::string Shader::ReadFile(const char* fileLocation)
{
  std::string content;
  std::fstream file(fileLocation, std::ios::in);

  if (!file.is_open())
  {
    printf("Failed to read %s!", fileLocation);
  }

  std::string line = "";

  while (!file.eof())
  {
    std::getline(file, line);
    content.append(line + '\n');
  }

  file.close();

  return content;
}

GLuint Shader::GetProjectionLocation()
{
  return uniformProjection;
}
GLuint Shader::GetModelLocation()
{
  return uniformModel;
}


GLuint Shader::GetViewLocation()
{
  return uniformView;
}


GLuint Shader::GetAmbientIntensityLocation()
{
  return uniformDirectionalLight.uniformAmbientIntensity;
}
GLuint Shader::GetAmbientColourLocation()
{
  return uniformDirectionalLight.uniformColour;
}

GLuint Shader::GetDiffuseIntensityLocation()
{
  return uniformDirectionalLight.uniformDiffuseIntensity;
}
GLuint Shader::GetDirectionLocation()
{
  return uniformDirectionalLight.uniformDirection;
}

GLuint Shader::GetSpecularIntensityLocation()
{
  return uniformSpecularIntensity;
}

GLuint Shader::GetShininessLocation()
{
  return uniformShininess;
}


GLuint Shader::GetEyePosition()
{
  return uniformEyePosition;
}

GLuint Shader::GetOmniLightPosLocation()
{
  return uniformOmniLightPos;
}

GLuint Shader::GetFarPlaneLocation()
{
  return uniformFarPlane;
}

void Shader::UseShader()
{
  glUseProgram(shaderID);
}
void Shader::ClearShader()
{
  if (shaderID != 0)
  {
    glDeleteProgram(shaderID);
    shaderID = 0;
  }

  uniformModel = 0;
  uniformProjection = 0;
}
Shader::~Shader()
{
  ClearShader();
}
void Shader::CompileShader(const char* vertexCode, const char* fragmentCode)
{
  shaderID = glCreateProgram();

  if (!shaderID)
  {
    printf("Error creating shader program!\n");
    return;
  }

  AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
  AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

  dc_CompileProgram();
}

void Shader::CompileShader(const char* vertexCode,const char* geometryCode, const char* fragmentCode)
{
  shaderID = glCreateProgram();

  if (!shaderID)
  {
    printf("Error creating shader program!\n");
    return;
  }

  AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
  AddShader(shaderID, geometryCode, GL_GEOMETRY_SHADER);
  AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

  dc_CompileProgram();
}

void Shader::SetupDirectionalLight(DirectionalLight* dLight)
{
  dLight->UseLight(
    uniformDirectionalLight.uniformAmbientIntensity,
    uniformDirectionalLight.uniformColour,
    uniformDirectionalLight.uniformDiffuseIntensity,
    uniformDirectionalLight.uniformDirection
  );

  // Set DirectionalShadowMap taxture unit to slot 2.
  //glUniform1i(uniformDirectionalShadowMap, 2);

}

void Shader::dc_SetDirectionalLight(DirectionalLight* dLight)
{
  dLight->UseLight(
    uniformDirectionalLight.uniformAmbientIntensity,
    uniformDirectionalLight.uniformColour,
    uniformDirectionalLight.uniformDiffuseIntensity,
    uniformDirectionalLight.uniformDirection
  );

  // Texture 1 is used for actual texture of mesh
  dLight->dc_GetShadowMap()->Read(GL_TEXTURE2);

  // Set DirectionalShadowMap taxture unit to slot 2.
  glUniform1i(uniformDirectionalShadowMap, 2);

}

void Shader::SetPointLights(
  const std::map<size_t, Component*>& pointLights,
  size_t textureUnit,
  size_t offset
)
{
  // Set number of point lights to shader.
  glUniform1i(uniformPointLightCount, static_cast<int>(pointLights.size()));

  // Iterate through all point lights and set their uniforms.
  size_t i = 0;
  for (auto it : pointLights)
  {
    PointLight* pointLight = static_cast<PointLight*>(it.second);

    pointLight->UseLight(
      uniformPointLight[i].uniformAmbientIntensity,
      uniformPointLight[i].uniformColour,
      uniformPointLight[i].uniformDiffuseIntensity,
      uniformPointLight[i].uniformPosition,
      uniformPointLight[i].uniformConstant,
      uniformPointLight[i].uniformLinear,
      uniformPointLight[i].uniformExponent
    );

    pointLight->dc_GetShadowMap()->Read(static_cast<GLenum>(GL_TEXTURE0 + textureUnit + i));

    glUniform1i(uniformOmniShadowMap[i + offset].uniformShadowMap, static_cast<GLint>(textureUnit + i));
    glUniform1f(uniformOmniShadowMap[i + offset].uniformFarPlane, pointLight->GetFarPlane());

    ++i;
  } 
}

void Shader::SetSpotLights(
  const std::map<size_t, Component*>& spotLights,
  size_t textureUnit,
  size_t offset)
{

  glUniform1i(uniformSpotLightCount, static_cast<int>(spotLights.size()));

  size_t i = 0;
  for (auto it : spotLights) {

    SpotLight* spotLight = static_cast<SpotLight*>(it.second);

    spotLight->UseLight(
      uniformSpotLight[i].uniformAmbientIntensity,
      uniformSpotLight[i].uniformColour,
      uniformSpotLight[i].uniformDiffuseIntensity,
      uniformSpotLight[i].uniformPosition,
      uniformSpotLight[i].uniformDirection,
      uniformSpotLight[i].uniformConstant,
      uniformSpotLight[i].uniformLinear,
      uniformSpotLight[i].uniformExponent,
      uniformSpotLight[i].uniformEdge
    );

    spotLight->dc_GetShadowMap()->Read(static_cast<GLenum>(GL_TEXTURE0 + textureUnit + i));

    glUniform1i(uniformOmniShadowMap[i + offset].uniformShadowMap, static_cast<GLint>(textureUnit + i));
    glUniform1f(uniformOmniShadowMap[i + offset].uniformFarPlane, spotLight->GetFarPlane());

    ++i;
  }
}



void Shader::dc_CompileProgram()
{
  GLint result = 0;
  GLchar eLog[1024] = { 0 };

  // Link shader
  glLinkProgram(shaderID);
  glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
  if (!result)
  {
    glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
    printf("Error linking program: '%s'\n", eLog);
    return;
  }

  // Grab shader uniform variable by it's name (ID)

  _ul_bIsSkeletonAnimated = glGetUniformLocation(shaderID, "bIsSkeletonAnimated");

  uniformModel = glGetUniformLocation(shaderID, "model");
  uniformProjection = glGetUniformLocation(shaderID, "projection");
  uniformView = glGetUniformLocation(shaderID, "view");
  uniformDirectionalLight.uniformColour = glGetUniformLocation(shaderID, "directionalLight.base.colour");
  uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.base.ambientIntensity");
  uniformDirectionalLight.uniformDirection = glGetUniformLocation(shaderID, "directionalLight.direction");
  uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.base.diffuseIntensity");
  uniformSpecularIntensity = glGetUniformLocation(shaderID, "material.specularIntensity");
  uniformShininess = glGetUniformLocation(shaderID, "material.shininess");
  uniformEyePosition = glGetUniformLocation(shaderID, "eyePosition");


  // Bind point lights uniforms to shader
  uniformPointLightCount = glGetUniformLocation(shaderID, "pointLightCount");
  for (size_t i = 0; i < MAX_POINT_LIGHTS; ++i)
  {
    char lockBuff[100] = { '\0' };
    snprintf(lockBuff, sizeof(lockBuff), "pointLights[%zd].base.colour", i);
    uniformPointLight[i].uniformColour = glGetUniformLocation(shaderID, lockBuff);
    snprintf(lockBuff, sizeof(lockBuff), "pointLights[%zd].base.ambientIntensity", i);
    uniformPointLight[i].uniformAmbientIntensity = glGetUniformLocation(shaderID, lockBuff);
    snprintf(lockBuff, sizeof(lockBuff), "pointLights[%zd].base.diffuseIntensity", i);
    uniformPointLight[i].uniformDiffuseIntensity = glGetUniformLocation(shaderID, lockBuff);

    snprintf(lockBuff, sizeof(lockBuff), "pointLights[%zd].position", i);
    uniformPointLight[i].uniformPosition = glGetUniformLocation(shaderID, lockBuff);
    snprintf(lockBuff, sizeof(lockBuff), "pointLights[%zd].constant", i);
    uniformPointLight[i].uniformConstant = glGetUniformLocation(shaderID, lockBuff);
    snprintf(lockBuff, sizeof(lockBuff), "pointLights[%zd].linear", i);
    uniformPointLight[i].uniformLinear = glGetUniformLocation(shaderID, lockBuff);
    snprintf(lockBuff, sizeof(lockBuff), "pointLights[%zd].exponent", i);
    uniformPointLight[i].uniformExponent = glGetUniformLocation(shaderID, lockBuff);
  }

  // Bind point lights uniforms to shader
  uniformSpotLightCount = glGetUniformLocation(shaderID, "spotLightCount");
  for (size_t i = 0; i < MAX_SPOT_LIGHTS; ++i)
  {
    char lockBuff[100] = { '\0' };
    // Light members
    snprintf(lockBuff, sizeof(lockBuff), "spotLights[%zd].base.base.colour", i);
    uniformSpotLight[i].uniformColour = glGetUniformLocation(shaderID, lockBuff);
    snprintf(lockBuff, sizeof(lockBuff), "spotLights[%zd].base.base.ambientIntensity", i);
    uniformSpotLight[i].uniformAmbientIntensity = glGetUniformLocation(shaderID, lockBuff);
    snprintf(lockBuff, sizeof(lockBuff), "spotLights[%zd].base.base.diffuseIntensity", i);
    uniformSpotLight[i].uniformDiffuseIntensity = glGetUniformLocation(shaderID, lockBuff);

    // Point light members
    snprintf(lockBuff, sizeof(lockBuff), "spotLights[%zd].base.position", i);
    uniformSpotLight[i].uniformPosition = glGetUniformLocation(shaderID, lockBuff);
    snprintf(lockBuff, sizeof(lockBuff), "spotLights[%zd].base.constant", i);
    uniformSpotLight[i].uniformConstant = glGetUniformLocation(shaderID, lockBuff);
    snprintf(lockBuff, sizeof(lockBuff), "spotLights[%zd].base.linear", i);
    uniformSpotLight[i].uniformLinear = glGetUniformLocation(shaderID, lockBuff);
    snprintf(lockBuff, sizeof(lockBuff), "spotLights[%zd].base.exponent", i);
    uniformSpotLight[i].uniformExponent = glGetUniformLocation(shaderID, lockBuff);

    // Spot light members
    snprintf(lockBuff, sizeof(lockBuff), "spotLights[%zd].direction", i);
    uniformSpotLight[i].uniformDirection = glGetUniformLocation(shaderID, lockBuff);
    snprintf(lockBuff, sizeof(lockBuff), "spotLights[%zd].edge", i);
    uniformSpotLight[i].uniformEdge = glGetUniformLocation(shaderID, lockBuff);
  }

  for (int i = 0; i < MAX_POINT_LIGHTS + MAX_SPOT_LIGHTS; ++i)
  {
    char lockBuff[100] = { '\0' };
    snprintf(lockBuff, sizeof(lockBuff), "omniShadowMaps[%d].shadowMap", i);
    uniformOmniShadowMap[i].uniformShadowMap = glGetUniformLocation(shaderID, lockBuff);

    snprintf(lockBuff, sizeof(lockBuff), "omniShadowMaps[%d].farPlane", i);
    uniformOmniShadowMap[i].uniformFarPlane = glGetUniformLocation(shaderID, lockBuff);

  }


  uniformTexture = glGetUniformLocation(shaderID, "theTexture");
  uniformDirectionalLightTransform = glGetUniformLocation(shaderID, "directionalLightTransform");
  uniformDirectionalShadowMap = glGetUniformLocation(shaderID, "directionalShadowMap");

  uniformOmniLightPos = glGetUniformLocation(shaderID, "lightPos");
  uniformFarPlane = glGetUniformLocation(shaderID, "farPlane");

  for (int i = 0; i < 6; ++i)
  {
    char lockBuff[100] = { '\0' };
    snprintf(lockBuff, sizeof(lockBuff), "lightMatrices[%d]", i);
    uniformLightMatrices[i] = glGetUniformLocation(shaderID, lockBuff);

  }

}

void Shader::CompileProgram()
{
  GLint result = 0;
  GLchar eLog[1024] = { 0 };

  // Link shader
  glLinkProgram(shaderID);
  glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
  if (!result)
  {
    glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
    printf("Error linking program: '%s'\n", eLog);
    return;
  }

  // Grab shader uniform variable by it's name (ID)

  //_ul_bIsSkeletonAnimated = glGetUniformLocation(shaderID, "bIsSkeletonAnimated");

  //uniformModel = glGetUniformLocation(shaderID, "model");
  //uniformProjection = glGetUniformLocation(shaderID, "projection");
  //uniformView = glGetUniformLocation(shaderID, "view");
  //uniformDirectionalLight.uniformColour = glGetUniformLocation(shaderID, "directionalLight.base.colour");
  //uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.base.ambientIntensity");
  //uniformDirectionalLight.uniformDirection = glGetUniformLocation(shaderID, "directionalLight.direction");
  //uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.base.diffuseIntensity");
  //uniformSpecularIntensity = glGetUniformLocation(shaderID, "material.specularIntensity");
  //uniformShininess = glGetUniformLocation(shaderID, "material.shininess");
  //uniformEyePosition = glGetUniformLocation(shaderID, "eyePosition");


  //// Bind point lights uniforms to shader
  //uniformPointLightCount = glGetUniformLocation(shaderID, "pointLightCount");
  //for (size_t i = 0; i < MAX_POINT_LIGHTS; ++i)
  //{
  //  char lockBuff[100] = { '\0' };
  //  snprintf(lockBuff, sizeof(lockBuff), "pointLights[%zd].base.colour", i);
  //  uniformPointLight[i].uniformColour = glGetUniformLocation(shaderID, lockBuff);
  //  snprintf(lockBuff, sizeof(lockBuff), "pointLights[%zd].base.ambientIntensity", i);
  //  uniformPointLight[i].uniformAmbientIntensity = glGetUniformLocation(shaderID, lockBuff);
  //  snprintf(lockBuff, sizeof(lockBuff), "pointLights[%zd].base.diffuseIntensity", i);
  //  uniformPointLight[i].uniformDiffuseIntensity = glGetUniformLocation(shaderID, lockBuff);

  //  snprintf(lockBuff, sizeof(lockBuff), "pointLights[%zd].position", i);
  //  uniformPointLight[i].uniformPosition = glGetUniformLocation(shaderID, lockBuff);
  //  snprintf(lockBuff, sizeof(lockBuff), "pointLights[%zd].constant", i);
  //  uniformPointLight[i].uniformConstant = glGetUniformLocation(shaderID, lockBuff);
  //  snprintf(lockBuff, sizeof(lockBuff), "pointLights[%zd].linear", i);
  //  uniformPointLight[i].uniformLinear = glGetUniformLocation(shaderID, lockBuff);
  //  snprintf(lockBuff, sizeof(lockBuff), "pointLights[%zd].exponent", i);
  //  uniformPointLight[i].uniformExponent = glGetUniformLocation(shaderID, lockBuff);
  //}

  //// Bind point lights uniforms to shader
  //uniformSpotLightCount = glGetUniformLocation(shaderID, "spotLightCount");
  //for (size_t i = 0; i < MAX_SPOT_LIGHTS; ++i)
  //{
  //  char lockBuff[100] = { '\0' };
  //  // Light members
  //  snprintf(lockBuff, sizeof(lockBuff), "spotLights[%zd].base.base.colour", i);
  //  uniformSpotLight[i].uniformColour = glGetUniformLocation(shaderID, lockBuff);
  //  snprintf(lockBuff, sizeof(lockBuff), "spotLights[%zd].base.base.ambientIntensity", i);
  //  uniformSpotLight[i].uniformAmbientIntensity = glGetUniformLocation(shaderID, lockBuff);
  //  snprintf(lockBuff, sizeof(lockBuff), "spotLights[%zd].base.base.diffuseIntensity", i);
  //  uniformSpotLight[i].uniformDiffuseIntensity = glGetUniformLocation(shaderID, lockBuff);

  //  // Point light members
  //  snprintf(lockBuff, sizeof(lockBuff), "spotLights[%zd].base.position", i);
  //  uniformSpotLight[i].uniformPosition = glGetUniformLocation(shaderID, lockBuff);
  //  snprintf(lockBuff, sizeof(lockBuff), "spotLights[%zd].base.constant", i);
  //  uniformSpotLight[i].uniformConstant = glGetUniformLocation(shaderID, lockBuff);
  //  snprintf(lockBuff, sizeof(lockBuff), "spotLights[%zd].base.linear", i);
  //  uniformSpotLight[i].uniformLinear = glGetUniformLocation(shaderID, lockBuff);
  //  snprintf(lockBuff, sizeof(lockBuff), "spotLights[%zd].base.exponent", i);
  //  uniformSpotLight[i].uniformExponent = glGetUniformLocation(shaderID, lockBuff);

  //  // Spot light members
  //  snprintf(lockBuff, sizeof(lockBuff), "spotLights[%zd].direction", i);
  //  uniformSpotLight[i].uniformDirection = glGetUniformLocation(shaderID, lockBuff);
  //  snprintf(lockBuff, sizeof(lockBuff), "spotLights[%zd].edge", i);
  //  uniformSpotLight[i].uniformEdge = glGetUniformLocation(shaderID, lockBuff);
  //}

  //for (int i = 0; i < MAX_POINT_LIGHTS + MAX_SPOT_LIGHTS; ++i)
  //{
  //  char lockBuff[100] = { '\0' };
  //  snprintf(lockBuff, sizeof(lockBuff), "omniShadowMaps[%d].shadowMap", i);
  //  uniformOmniShadowMap[i].uniformShadowMap = glGetUniformLocation(shaderID, lockBuff);

  //  snprintf(lockBuff, sizeof(lockBuff), "omniShadowMaps[%d].farPlane", i);
  //  uniformOmniShadowMap[i].uniformFarPlane = glGetUniformLocation(shaderID, lockBuff);

  //}


  //uniformTexture = glGetUniformLocation(shaderID, "theTexture");
  //uniformDirectionalLightTransform = glGetUniformLocation(shaderID, "directionalLightTransform");
  //uniformDirectionalShadowMap = glGetUniformLocation(shaderID, "directionalShadowMap");

  //uniformOmniLightPos = glGetUniformLocation(shaderID, "lightPos");
  //uniformFarPlane = glGetUniformLocation(shaderID, "farPlane");

  //for (int i = 0; i < 6; ++i)
  //{
  //  char lockBuff[100] = { '\0' };
  //  snprintf(lockBuff, sizeof(lockBuff), "lightMatrices[%d]", i);
  //  uniformLightMatrices[i] = glGetUniformLocation(shaderID, lockBuff);

  //}

}


void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
  GLuint theShader = glCreateShader(shaderType);

  const GLchar* theCode[1];
  theCode[0] = shaderCode;

  GLint codeLength[1];
  codeLength[0] = static_cast<GLuint>(strlen(shaderCode));

  glShaderSource(theShader, 1, theCode, codeLength);
  glCompileShader(theShader);

  GLint result = 0;
  GLchar eLog[1024] = { 0 };

  glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
  if (!result)
  {
    glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
    printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
    return;
  }
  glAttachShader(theProgram, theShader);
}

void Shader::SetTexture(GLuint textureUnit)
{
  glUniform1i(uniformTexture, textureUnit);
  return;
}
void Shader::SetDirectionalShadowMap(GLuint textureUnit)
{
  glUniform1i(uniformDirectionalShadowMap, textureUnit);
  return;
}

void Shader::SetDirectionalLightTransform(glm::mat4* lTransform)
{
  glUniformMatrix4fv(uniformDirectionalLightTransform, 1, GL_FALSE, glm::value_ptr(*lTransform));
  return;
}

void Shader::SetOmniLightMatrices(std::vector<glm::mat4> lightMatrices)
{
  for (int i = 0; i < 6; ++i)
  {
    glUniformMatrix4fv(uniformLightMatrices[i], 1, GL_FALSE, glm::value_ptr(lightMatrices[i]));
  }
}
