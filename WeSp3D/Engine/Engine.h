#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>
#include <vector>
#include <memory>
#include <queue>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#pragma warning(push, 3)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#pragma warning(pop)

#include "stb_image.h"
#include <assimp/Importer.hpp>
#include "Command.h"
#include "Skybox.h"
#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include "Material.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Model.h"


// =============

#include "Logger.h"

#include "macros.h"
#include "config_engine.h"
#include "IModuleState.h"
#include "IErrorLogging.h"
#include "IMainEngineModule.h"

#include "EngineContext.h"
#include "GameContext.h"
#include "SceneContext.h"
#include "BaseEngine.h"

#include "Instance.h"

#include "EngineAPI.h"
#include "EntityManager.h"
#include "InputManager.h"
#include "NetworkManager.h"
#include "OutputManager.h"
#include "RenderingManager.h"
#include "SceneManager.h"
#include "SimulationManager.h"
#include "AudioManager.h"
#include "ComponentManager.h"


//#include "AnimatedModel.h"

// -------------------------

#include "SkeletalModel.h"


using namespace WeSp;

namespace WeSp
{
class Engine :
  public IModuleState, public IErrorLogging,
  public BaseEngine
{
public:
  Engine(Instance* instance);
  virtual ~Engine();

  bool Initialize();
  bool Run();
  bool Terminate();

  std::shared_ptr<EngineAPI> GetEngineAPI();

public:
  Instance* _pInstance;

  // Main Engine modules
  std::map<int, std::shared_ptr<IMainEngineModule>> _modules;

  EngineContext _engineContext;
  GameContext _gameContext;
  SceneContext _sceneContext;


  // ------------------------


  class SceneObject
  {
  public:
    Mesh* _pMesh;
    glm::vec3 _rotationAxis;
    float _angle;
    glm::vec3 _translation;
    glm::vec3 _scale;

    SceneObject(
      Mesh* pMesh, 
      glm::vec3 rotationAxis, float angle, 
      glm::vec3 translation, 
      glm::vec3 scale) :
      _pMesh(pMesh), _rotationAxis(rotationAxis), _angle(angle), _translation(translation), _scale(scale)
    {}

  };

  // Object ID attr
  int globObjID;
  
  // Shader uniform handles
  GLuint uf_bIsSkeletonAnimated = 0;
  GLuint uniformProjection = 0;
  GLuint uniformModel = 0;
  GLuint uniformView = 0;
  GLuint uniformSpecularIntensity = 0;
  GLuint uniformShininess = 0;
  GLuint uniformEyePosition = 0;
  GLuint uniformOmniLightPos = 0;
  GLuint uniformFarPlane = 0;

  SkeletalModel dude;
  SkeletalModel wolf;
  SkeletalModel plane;


  Skybox skybox;
  std::vector<Mesh*> meshList;
  

  std::map<int, SceneObject> editorMeshList;

  // Shaders for objects at scene
  std::vector<Shader*> shaderList;

  // Shadow map shaders
  Shader directionalShadowShader;
  Shader omniShadowShader;

  Camera camera;

  //Shader animatedShader;

  Texture brickTexture;
  Texture dirtTexture;
  Texture plainTexture;

  Material shinyMaterial;
  Material dullMaterial;

  Model xwing;
  Model blackhawk;
  SkeletalModel dude2;

  DirectionalLight mainLight;
  PointLight pointLights[MAX_POINT_LIGHTS];
  SpotLight spotLights[MAX_SPOT_LIGHTS];

  unsigned int pointLightCount = 0;
  unsigned int spotLightCount = 0;

  float blackhawkAngle = 0.0f;

  GLfloat deltaTime = 0.0f;
  GLfloat lastTime = 0.0f;

  const float toRadians = (float)3.14159265 / 180.0f;

  // Suppress unreferenced warnings
#pragma warning(disable : 4100)

  // Shdaer files
  const char* vShader = "shaders/shader.vert";
  const char* fShader = "shaders/shader.frag";

  

  bool HandleCommandDeleteObjectId(std::vector<int> intData)
  {

    editorMeshList.erase(intData[0]);
    ENGINE_API->PushEditorCommand<int>(eCommandType::DeletedObjectId, intData);

    return true;
  }

  bool HandleCommandCreateBlock(std::vector<float> floatData)
  {
    // Extract data
    float xPos = floatData[0];
    float yPos = floatData[1];
    float zPos = floatData[2];

    // in  half thos
    float width = floatData[3] / 2;
    float height = floatData[4] / 2;
    float length = floatData[5] / 2;

    float xRot = floatData[6];
    float yRot = floatData[7];
    float zRot = floatData[8];
    float angle = floatData[9] * ((float)3.14159265 / 180.0f);

    float xScale = floatData[10];
    float yScale = floatData[11];
    float zScale = floatData[12];
    
    std::vector<float> blockVertices = {
      -width, height, -length,		  0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
      -width, -height, -length,	    0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
      width, height, -length,		      0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
      width, -height, -length,		    0.0f, 0.0f,		0.0f, 0.0f, 0.0f,

      -width, height, length,		    0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
      width, height, length,		  0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
      -width, -height, length,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
      width, -height, length,		  0.0f, 0.0f,		0.0f, 0.0f, 0.0f
    };

    // Create vrtices and indices
    std::vector<unsigned int>  blockIndices = {
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

    // Mesh
    Mesh* blockMesh = new Mesh();    
    blockMesh->CreateMesh(blockVertices, blockIndices, true);


    editorMeshList.insert(std::pair<int, SceneObject> (
      globObjID, 
      SceneObject(
        blockMesh, 
        glm::vec3(xRot, yRot, zRot), angle, 
        glm::vec3(xPos, yPos, zPos), 
        glm::vec3(xScale, yScale, zScale))
      )
    );
    

    std::vector<int> data;
    data.push_back(globObjID);
    ++globObjID;

    ENGINE_API->PushEditorCommand<int>(eCommandType::CreatedObjectId, data);

    return true;
  }


  bool HandleCommandCreateSphere(std::vector<float> floatData)
  {
    int numSlices = 30;
    int numStack = 40;

    float deltaSlice = static_cast<float>((float)2 / numSlices);
    float deltaStack = static_cast<float>((float)(2 * 3.14) / numStack);

    // Extract data
    float xPos = floatData[0];
    float yPos = floatData[1];
    float zPos = floatData[2];

    float xWidth = floatData[3];
    float yWidth = floatData[4];
    float zWIdth = floatData[5];

   /* float xRot = floatData[6];
    float yRot = floatData[7];
    float zRot = floatData[8];
    float angle = floatData[9] * toRadians;*/

    float xScale = floatData[6];
    float yScale = floatData[7];
    float zScale = floatData[8];
    
    std::vector<GLfloat> blockVertices;
    std::vector<unsigned int> blockIndices;

    //-1.0f *, 1.0f, -1.0f,     0.0f, 0.0f,     0.0f, 0.0f, 0.0f,

    float radius = 1.0f;

    // RENDERING_MANAGER->MESH_MANAGER->CreatePrimitive(eMeshPrimitives::Block, x, x, x, x, x);

    // Mesh
    Mesh* blockMesh = new Mesh();
    blockMesh->CreateMesh(blockVertices, blockIndices, true);

    editorMeshList.insert(std::pair<int, SceneObject>(
      globObjID,
      SceneObject(
        blockMesh,
        glm::vec3(1.0f, 1.0f, 1.0f), 0,
        glm::vec3(xPos, yPos, zPos),
        glm::vec3(xScale, yScale, zScale))
      )
    );

    Engine::GetGLErrors(__FILE__, __LINE__);
    std::vector<int> data;
    data.push_back(globObjID);
    ++globObjID;

    ENGINE_API->PushEditorCommand<int>(eCommandType::CreatedObjectId, data);

    // model to world transform matrix
    return true;
  }
  
  static void GetGLErrors(const char* file, unsigned int lineNum)
  {
    const GLubyte*  stdee;
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
      // Process/log the error.
      stdee = gluErrorString(err);
      printf("ERROR GL: %s , file: %s, line: %d\n", stdee, file, lineNum);
    }
  }
  
  void CreateObjects()
  {
    std::vector<unsigned int> indices =
    {
      0, 3, 1,
      1, 3, 2,
      2, 3, 0,
      0, 1, 2
    };

    std::vector<GLfloat> vertices = {
      // x      y     z     u     v       nx    ny     nz
      -1.0f, -1.0f, -0.6f,   0.0f, 0.0f,   0.0f, 0.0f, 0.0f,
      0.0f, -1.0f, 1.0f,    0.5f, 0.0f,   0.0f, 0.0f, 0.0f,
      1.0f, -1.0f, -0.6f,    1.0f, 0.0f,   0.0f, 0.0f, 0.0f,
      0.0f, 1.0f, 0.0f,     0.5f, 1.0f,   0.0f, 0.0f, 0.0f
    };


    std::vector<unsigned int> floorIndices = {
      0, 2, 1,
      1, 2, 3
    };

    std::vector<GLfloat> floorVertices = {
      -10.0f, 0.0f, -10.0f,   0.0f, 0.0f,     0.0f, -1.0f, 0.0f,
      10.0f, 0.0f, -10.0f,    10.0f, 0.0f,    0.0f, -1.0f, 0.0f,
      -10.0f, 0.0f, 10.0f,    0.0f, 10.0f,    0.0f, -1.0f, 0.0f,
      10.0f, 0.0f, 10.0f,      10.0f, 10.0f,  0.0f, -1.0f, 0.0f,
    };


    std::vector<unsigned int> indices2 =
    {
      0,1,3,
      1,2,3,
      0,4,1,
      1,5,4,
      1,5,6,
      1,6,2,
      6,2,7,
      7,2,3,
      3,7,4,
      0,4,3,
      4,5,6,
      4,6,7
    };

    std::vector<GLfloat> vertices2 = {
      -1.0f, 0.0f, -1.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,
      1.0f, 0.0f, -1.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 1.0f, 1.0f, 1.0f,     0.0f, 0.0f, 0.0f,
      -1.0f, 0.0f, 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,
      -0.5f, 0.5f, -0.5f, 0.25f, 0.25f, 0.0f, 0.0f, 0.0f,
      0.5f, 0.5f, -0.5f, 0.75f, 0.25f,  0.0f, 0.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 0.75f, 0.75f,   0.0f, 0.0f, 0.0f,
      -0.5f, 0.5f, 0.5f, 0.25f, 0.75f,  0.0f, 0.0f, 0.0f
    };

    Mesh* obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, true);

    Mesh* obj2 = new Mesh();
    obj2->CreateMesh(vertices, indices, true);


    Mesh* obj3 = new Mesh(floorVertices, floorIndices);

    meshList.push_back(obj1);
    meshList.push_back(obj2);
    meshList.push_back(obj3);
  }

  void CreateShaders()
  {
    Shader* shader1 = new Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(shader1);

    directionalShadowShader.CreateFromFiles(
      "shaders/directional_shadow_map.vert", 
      "shaders/directional_shadow_map.frag"
    );

    omniShadowShader.CreateFromFiles(
      "shaders/omni_shadow_map.vert", 
      "shaders/omni_shadow_map.geom", 
      "shaders/omni_shadow_map.frag"
    );
  }

  void RenderScenePlain()
  {

    glm::mat4 model = std::move(glm::mat4(1.0f));
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    meshList[0]->RenderMesh();


    model = std::move(glm::mat4(1.0f));
    model = glm::translate(model, glm::vec3(0.0f, 4.0f, -2.5f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    meshList[1]->RenderMesh();


    model = std::move(glm::mat4(1.0f));
    model = glm::translate(model, glm::vec3(0.0f, -2.0f, -0.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    meshList[2]->RenderMesh();


    model = std::move(glm::mat4(1.0f));
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 10.0f));
    model = glm::scale(model, glm::vec3(0.006f, 0.006f, 0.006f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    xwing.RenderModel();


    // Render editor objects
    for (std::map<int, SceneObject>::iterator it = editorMeshList.begin(); it != editorMeshList.end(); ++it)
    {
      SceneObject sceneObject = (*it).second;

      // Calculate model->world transform matrix
      model = std::move(glm::mat4(1.0f));
      model = glm::translate(model, sceneObject._translation);
      model = glm::rotate(model, sceneObject._angle, sceneObject._rotationAxis);
      model = glm::scale(model, sceneObject._scale);

      // Bind matrix to shader uniform
      glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
      sceneObject._pMesh->RenderMesh();
    }


    blackhawkAngle -= 0.2f;
    if (blackhawkAngle > 360.0f)
    {
      blackhawkAngle = 0.2f;
    }

    model = std::move(glm::mat4(1.0f));
    model = glm::rotate(model, blackhawkAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(-9.0f, 2 + (float)(sin(glfwGetTime()) * 0.5 * 3.14), 0.0f));
    model = glm::rotate(model, -15.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::rotate(model, -90.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    blackhawk.RenderModel();
  }

  void RenderScene()
  {

    glm::mat4 model = std::move(glm::mat4(1.0f));
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    brickTexture.UseTexture();
    shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
    meshList[0]->RenderMesh();


    model = std::move(glm::mat4(1.0f));
    model = glm::translate(model, glm::vec3(0.0f, 4.0f, -2.5f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    dirtTexture.UseTexture();
    shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
    meshList[1]->RenderMesh();


    model = std::move(glm::mat4(1.0f));
    model = glm::translate(model, glm::vec3(0.0f, -2.0f, -0.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    dirtTexture.UseTexture();
    shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
    meshList[2]->RenderMesh();

    model = std::move(glm::mat4(1.0f));
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 10.0f));
    model = glm::scale(model, glm::vec3(0.006f, 0.006f, 0.006f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
    xwing.RenderModel();

    // Render editor objects
    for (std::map<int, SceneObject>::iterator it = editorMeshList.begin(); it != editorMeshList.end(); ++it)
    {
      SceneObject sceneObject = (*it).second;

      // Calculate model->world transform matrix
      model = std::move(glm::mat4(1.0f));
      model = glm::translate(model, sceneObject._translation);
      model = glm::rotate(model, sceneObject._angle, sceneObject._rotationAxis);
      model = glm::scale(model, sceneObject._scale);

      // Bind matrix to shader uniform
      glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
  
      // Set texture to use
      // TODO: implement
      plainTexture.UseTexture();

      // Set Material
      shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
      sceneObject._pMesh->RenderMesh();
    }



    blackhawkAngle -= 0.2f;
    if (blackhawkAngle > 360.0f)
    {
      blackhawkAngle = 0.2f;
    }

    model = std::move(glm::mat4(1.0f));
    model = glm::rotate(model, blackhawkAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(-9.0f, 2 + (float)(sin(glfwGetTime()) * 0.5 * 3.14), 0.0f));
    model = glm::rotate(model, -15.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::rotate(model, -90.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
    blackhawk.RenderModel();

  }

  void DirectionalShadowMapPass(DirectionalLight* light)
  {
    directionalShadowShader.UseShader();

    // Setup viewport same as frame buffer
    glViewport(0, 0, light->GetShadowMap()->GetShadowWidth(), light->GetShadowMap()->GetShadowHeight());

    // Prepare depth buffer to write into it
    light->GetShadowMap()->Write();

    // CLear depth buffer
    glClear(GL_DEPTH_BUFFER_BIT);

    // Get handle to model uniform in shader
    uniformModel = directionalShadowShader.GetModelLocation();

    // Give it correctly calculated lightTransform matrix
    directionalShadowShader.SetDirectionalLightTransform(&light->CalculateLightTransform());

    directionalShadowShader.Validate();
    // Render objects in scene with their own shaders


    Engine::GetGLErrors(__FILE__, __LINE__);

    directionalShadowShader.SetIsSkeletonAnimated(false);
    RenderScenePlain();

    directionalShadowShader.SetIsSkeletonAnimated(true);
    RenderSceneXPlain(directionalShadowShader.GetShaderID());
   
    // Deatach from framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

  }

  void OmniShadowMapPass(PointLight* light)
  {
    omniShadowShader.UseShader();

    // Setup viewport same as frame buffer
    glViewport(0, 0, light->GetShadowMap()->GetShadowWidth(), light->GetShadowMap()->GetShadowHeight());

    // Prepare depth buffer to write into it
    light->GetShadowMap()->Write();

    // CLear depth buffer
    glClear(GL_DEPTH_BUFFER_BIT);

    // Get handle to model uniform in shader
    uniformModel = omniShadowShader.GetModelLocation();
    uniformOmniLightPos = omniShadowShader.GetOmniLightPosLocation();
    uniformFarPlane = omniShadowShader.GetFarPlaneLocation();

    // Bind to shader position of light in the World coordinates
    glUniform3f(uniformOmniLightPos, light->GetPosition().x, light->GetPosition().y, light->GetPosition().z);
    glUniform1f(uniformFarPlane, light->GetFarPlane());
    // Bind to shader 6 direction transofrm light metrices
    omniShadowShader.SetOmniLightMatrices(light->GetOmniLightModelToWorldMatrices());

    omniShadowShader.Validate();

    // Render objects in scene for omni light scene
    omniShadowShader.SetIsSkeletonAnimated(false);
    RenderScenePlain();

    omniShadowShader.SetIsSkeletonAnimated(true);
    RenderSceneXPlain(omniShadowShader.GetShaderID());

    // Deatach from framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  void RenderSceneX()
  {
    glm::mat4 model = std::move(glm::mat4(1.0f));
    model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
    model = glm::rotate(model, -90.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    
    dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
    
    std::vector<glm::mat4> Transforms;
    dude.boneTransform(glfwGetTime(), Transforms);
    
    for (unsigned int i = 0; i < Transforms.size(); ++i)
    {
      const std::string name = "gBones[" + std::to_string(i) + "]";
      GLuint boneTransform = glGetUniformLocation(shaderList[0]->GetShaderID(), name.c_str());
      glUniformMatrix4fv(boneTransform, 1, GL_FALSE, glm::value_ptr(Transforms[i]));
    }
    Engine::GetGLErrors(__FILE__, __LINE__);

    shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
    dude.render(shaderList[0]->GetShaderID());


    model = std::move(glm::mat4(1.0f));
    model = glm::translate(model, glm::vec3(-8.0f, -1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
        
    dude2.boneTransform(glfwGetTime(), Transforms);

    for (unsigned int i = 0; i < Transforms.size(); ++i)
    {
      const std::string name = "gBones[" + std::to_string(i) + "]";
      GLuint boneTransform = glGetUniformLocation(shaderList[0]->GetShaderID(), name.c_str());
      glUniformMatrix4fv(boneTransform, 1, GL_FALSE, glm::value_ptr(Transforms[i]));
    }

    dude2.render(shaderList[0]->GetShaderID());




  }


  void RenderSceneXPlain(GLuint shaderId)
  {
    glm::mat4 model = std::move(glm::mat4(1.0f));
    model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
    model = glm::rotate(model, -90.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

    std::vector<glm::mat4> Transforms;
    dude.boneTransform(glfwGetTime(), Transforms);

    for (unsigned int i = 0; i < Transforms.size(); ++i)
    {
      const std::string name = "gBones[" + std::to_string(i) + "]";
      GLuint boneTransform = glGetUniformLocation(shaderId, name.c_str());
      glUniformMatrix4fv(boneTransform, 1, GL_FALSE, glm::value_ptr(Transforms[i]));
    }
    Engine::GetGLErrors(__FILE__, __LINE__);

    dude.render(shaderList[0]->GetShaderID());

    model = std::move(glm::mat4(1.0f));
    model = glm::translate(model, glm::vec3(-8.0f, -1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

    dude2.boneTransform(glfwGetTime(), Transforms);

    for (unsigned int i = 0; i < Transforms.size(); ++i)
    {
      const std::string name = "gBones[" + std::to_string(i) + "]";
      GLuint boneTransform = glGetUniformLocation(shaderId, name.c_str());
      glUniformMatrix4fv(boneTransform, 1, GL_FALSE, glm::value_ptr(Transforms[i]));
    }

    dude2.render(shaderList[0]->GetShaderID());

  }


  void RenderPass(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
  {
    // Set correct viewport, just to be sure
    glViewport(0, 0, GAME_WINDOW_DEFAULT_WIDTH, GAME_WINDOW_DEFAULT_HEIGHT);

    // Clear window
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    skybox.DrawSkybox(viewMatrix, projectionMatrix);

    Engine::GetGLErrors(__FILE__, __LINE__);

    // Draw main scene
    shaderList[0]->UseShader();
    uniformModel = shaderList[0]->GetModelLocation();
    uniformProjection = shaderList[0]->GetProjectionLocation();
    uniformView = shaderList[0]->GetViewLocation();
    uniformEyePosition = shaderList[0]->GetEyePosition();
    uniformSpecularIntensity = shaderList[0]->GetSpecularIntensityLocation();
    uniformShininess = shaderList[0]->GetShininessLocation();

    // Set values in shader uniforms
    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniform3f(uniformEyePosition, camera.GetCameraPosition().x, camera.GetCameraPosition().y, camera.GetCameraPosition().z);

    shaderList[0]->SetDirectionalLight(&mainLight);
    shaderList[0]->SetPointLights(pointLights, pointLightCount, 3, 0);
    shaderList[0]->SetSpotLights(spotLights, spotLightCount, 3 + pointLightCount, pointLightCount);
    shaderList[0]->SetDirectionalLightTransform(&mainLight.CalculateLightTransform());

    // Texture 0 is used for actual texture of mesh
    mainLight.GetShadowMap()->Read(GL_TEXTURE2);
    // Shift everything by 1 so unused members of array in shader mapped into 0 wont collide types
    // Set normal texture to 1
    shaderList[0]->SetTexture(1);
    // Set shadow mapt texture to 1
    shaderList[0]->SetDirectionalShadowMap(2);

    // Set spotlight to our camera
    glm::vec3 lowerLight = camera.GetCameraPosition();
    lowerLight.y -= 0.5f;
    if (EngineContext::gTorchOn)
    {
      spotLights[1].SetFlash(lowerLight, camera.GetCameraDirection());
    }
    else
    {
      spotLights[1].SetFlash(glm::vec3(0.0f, -100.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
    }

    shaderList[0]->Validate();

    // Switch off skeletal animation shader.
    shaderList[0]->SetIsSkeletonAnimated(false);

    // Go ahead and render scene
    RenderScene();

    // Switch off skeletal animation shader.
    shaderList[0]->SetIsSkeletonAnimated(true);
    RenderSceneX();

  }


};

}