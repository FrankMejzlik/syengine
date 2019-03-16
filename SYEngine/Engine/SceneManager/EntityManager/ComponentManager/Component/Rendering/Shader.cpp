#include "Shader.h"

#include "Component.h"

using namespace SYE;

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
