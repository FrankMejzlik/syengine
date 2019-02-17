
#define STB_IMAGE_IMPLEMENTATION

#include "Skybox.h"

using namespace SYE;


Skybox::Skybox(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef, std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentSlots, std::vector<std::string> faceLocation):
  Component(pOwnerEntity, subModulesConstRef, primaryComponentSlots, false)
{
  _type = eType::SKYBOX;

  // Shader setup
  skyShader = new Shader(nullptr, subModulesConstRef, primaryComponentSlots);
  skyShader->CreateFromFiles(
    "shaders/skybox.vert", 
    "shaders/skybox.frag"
  );  
  
  uniformProjection = skyShader->GetProjectionLocation();
  uniformView = skyShader->GetViewLocation();

  // Texture setup
  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

  int width, height, bitDepth;


  for (size_t i = 0; i < 6; ++i)
  { 
    unsigned char* texData = stbi_load(faceLocation[i].c_str(), &width, &height, &bitDepth, 0);
    if (!texData)
    {
      printf("Failed to find %s\n", faceLocation[i].c_str());
      return;
    }

    glTexImage2D(
      static_cast<GLenum>(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i),
      0, // Mipmaps 
      static_cast<GLenum>(GL_RGB), // Data fomrat in GPU memory
      width,
      height,
      0,  // Legacy border
      static_cast<GLenum>(GL_RGB), // Type on input
      static_cast<GLenum>(GL_UNSIGNED_BYTE),
      texData
    );
    stbi_image_free(texData);
  }

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Mesh setup
  std::vector<unsigned int> skyboxIndices = {
    // front
    0, 1, 2,
    2, 1, 3,
    // right
    2, 3, 5,
    5, 3, 7,
    // back
    5, 7, 4,
    4, 7, 6,
    // left
    4, 6, 0,
    0, 6, 1,
    // top
    4, 0, 5,
    5, 0, 2,
    // bottom
    1, 6, 3,
    3, 6, 7
  };

  std::vector<float> skyboxVertices = {
    -1.0f, 1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
    -1.0f, -1.0f, -1.0f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
    1.0f, 1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
    1.0f, -1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,

    -1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 1.0f,		  0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
    -1.0f, -1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
    1.0f, -1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f
  };

  skyMesh = new Mesh(_pOwnerEntity, _subModules, primaryComponentSlots);
  skyMesh->CreateMesh(skyboxVertices, skyboxIndices);
}


Skybox::~Skybox()
{

}

void Skybox::DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
  // Cut all translate data
  viewMatrix = glm::mat4(glm::mat3(viewMatrix));

  // Disable depth mask for skybox - is is always in "infinite" distance
  glDepthMask(GL_FALSE);

  skyShader->UseShader();

  glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
  glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));

  // We will use only one shader, so can be 0
  glActiveTexture(GL_TEXTURE0);

  // bind texture... by default it is bind to )
  glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

  skyShader->Validate();

  skyMesh->RenderMesh();

  // Turn depth mask back on
  glDepthMask(GL_TRUE);
}
