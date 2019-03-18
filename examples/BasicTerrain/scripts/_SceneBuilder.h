#pragma once

/** 
* @file
* @breif Class @ref SYE::_SceneBuilder implementation
*/

#include <random>
#include <vector>

#include "_SceneBuilderBase.h"
#include "Script.h"
#include "Scene.h"
#include "Entity.h"
#include "MeshRenderer.h"
#include "Rigidbody.h"
#include "PointLight.h"

// Include all scripts you're gonna use
#include "game_script_includes.h"


#define cWidth 100ULL
#define cHeight 100ULL
#define cScale 1.5f

namespace SYE
{

/**
 * Class responsible for building initial Scene instance before launch
 *
 * This is derrived class of abstract _SceneBuilderBase. This is concrete implementation
 * for concrete game that is being scripted.
 * 
 */
class _SceneBuilder:
  public _SceneBuilderBase
{
public:
  /**
   * Builds initial scene
   *
   * This is special script that is executed exactly once before game itself starts.
   *
   * @param   Scene*  Pointer to Scene instance we are building
   * @return  void
   */
  virtual void SetupScene(Scene* pScene) override
  {
    // Create lights
    ConstructLighting(pScene);

    // Create terrain
    ConstructTerrain(pScene);

    // Create Scene 
    CreateCameras(pScene);

  }


private:

  /** 
   * Creates terrain for this Scene
   *
   *  @param  Scene*  Pointer to scene instance we're building
   *  @return void
   */
  void ConstructTerrain(Scene* pScene)
  {
    // Create random generator
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<float> randFromDistribution(0,2);

    /* 
     * Array of vertices - 8 dfloats per vertex
     * position    | tex coords |   normals
     * x, y, z,        u, v,       nx, ny, nz
     */
    std::vector<dfloat> verices;
    
    // Array of vertex indices - three indices per one triangle
    std::vector<unsigned int> indices;

    std::vector<Vector3f> faceNormals;
    

    // Iterate through height
    for (size_t i = 0ULL; i < cHeight; ++i)
    {
      // Iteratre through width
      for (size_t j = 0ULL; j < cWidth; ++j)
      {
        // Get random height
        dfloat height = randFromDistribution(rng);

        // x
        verices.push_back(i * cScale);

        // y
        verices.push_back(height * cScale);

        // z
        verices.push_back(j * cScale);

        // Push UVs
        if ((i + j) % 2 == 0)
        {
          verices.push_back(0.0f);
          verices.push_back(0.0f);
        }
        else
        {
          verices.push_back(1.0f);
          verices.push_back(1.0f);
        }
        
        // Push generic normal values
        verices.push_back(0.0f);
        verices.push_back(1.0f);
        verices.push_back(0.0f);
       
      }
    }

    // Accumulator for normals
    std::vector<std::pair<size_t, Vector3f>> vericesNormals;
    // Initialize with 0 contributors and zero vector
    vericesNormals.resize(cHeight * cWidth, std::make_pair(0ULL, Vector3f(0.0f, 0.0f, 0.0f)));

    size_t stride = 8ULL;

    // Iterate through height
    for (size_t i = 0ULL; i < cHeight - 1; ++i)
    {
      // Iteratre through width
      for (size_t j = 0ULL; j < cWidth - 1; ++j)
      {
        // First triangle
        indices.push_back((unsigned int)((i * cWidth) + j));
        indices.push_back((unsigned int)((i * cWidth) + j + 1));
        indices.push_back((unsigned int)(((i + 1) * cWidth) + j + 1));

        // Second triangle
        indices.push_back((unsigned int)(((i + 1) * cWidth) + j + 1));
        indices.push_back((unsigned int)(((i + 1) * cWidth) + j));
        indices.push_back((unsigned int)((i * cWidth) + j));

        // Calc normal of this face

        size_t topLeftIndex = ((i * cWidth) + j) * stride;
        Vector3f topLeft(
          verices[topLeftIndex], 
          verices[topLeftIndex + 1], 
          verices[topLeftIndex + 2]
          );

        size_t topRightIndex = ((i * cWidth) + j + 1) * stride;
        Vector3f topRight(
          verices[topRightIndex], 
          verices[topRightIndex + 1], 
          verices[topRightIndex + 2]
        );

        size_t bottomRightIndex = (((i + 1) * cWidth) + j + 1) * stride;
        Vector3f bottomRight(
          verices[bottomRightIndex], 
          verices[bottomRightIndex + 1], 
          verices[bottomRightIndex + 2]
        );

        size_t bottomLeftIndex = (((i + 1) * cWidth) + j) * stride;
        Vector3f bottomLeft(
          verices[bottomLeftIndex], 
          verices[bottomLeftIndex + 1], 
          verices[bottomLeftIndex + 2]
        );

        // Get edge vectors
        Vector3f top(topRight - topLeft);
        Vector3f middle(bottomRight - topLeft);
        Vector3f bottom(bottomLeft - topLeft);

        // Calculate face normals
        Vector3f n1 = Cross(middle, top);
        Vector3f n2 = Cross(bottom, middle);

        /*
         * Distribute normals to all adjecent verices
         */
        // Normal 1
        {
        // Top left
          {
            std::pair<size_t, Vector3f>& pair = vericesNormals[topLeftIndex / stride];
            // Increment counter of
            ++pair.first;
            // Add to current vector
            pair.second = pair.second + n1;
          }

          // Top right
          {
            std::pair<size_t, Vector3f>& pair = vericesNormals[topRightIndex / stride];
            // Increment counter of
            ++pair.first;
            // Add to current vector
            pair.second = pair.second + n1;
          }

          // Bottom right
          {
            std::pair<size_t, Vector3f>& pair = vericesNormals[bottomRightIndex / stride];
            // Increment counter of
            ++pair.first;
            // Add to current vector
            pair.second = pair.second + n1;
          }
        }

        // Normal 2
        {
          // Bottom right
          {
            std::pair<size_t, Vector3f>& pair = vericesNormals[bottomRightIndex / stride];
            // Increment counter of
            ++pair.first;
            // Add to current vector
            pair.second = pair.second + n2;
          }

          // Bottom left
          {
            std::pair<size_t, Vector3f>& pair = vericesNormals[bottomLeftIndex / stride];
            // Increment counter of
            ++pair.first;
            // Add to current vector
            pair.second = pair.second + n2;
          }

          // Top left
          {
            std::pair<size_t, Vector3f>& pair = vericesNormals[topLeftIndex / stride];
            // Increment counter of
            ++pair.first;
            // Add to current vector
            pair.second = pair.second + n2;
          }
        }

      }
    }


    size_t stride2 = 5ULL;

    size_t vertexIndex = 0ULL;

    // Summarize all result normals
    for (auto&& vertexPair : vericesNormals)
    {
      // Divide normal with number of contributors
      Vector3f totalNormal = vertexPair.second;

      // Normalize it
      totalNormal = Normalize(totalNormal);

      verices[(vertexIndex * stride) + stride2] = totalNormal.GetX();
      verices[(vertexIndex * stride) + stride2 + 1] = totalNormal.GetY();
      verices[(vertexIndex * stride) + stride2 + 2] = totalNormal.GetZ();

      ++vertexIndex;
    }

    // Create Entity representing terrain
    Entity* pTerrainEntity = pScene->CreateTerrain(
      Vector3f(0.0f, 0.0f, 0.0f),  // Position in the Scene
      Vector3f(0.0f, 0.0f, 0.0f),  // Rotation angles around X, Y, Z
      Vector3f(1.0f, 1.0f, 1.0f),  // Scale
      verices, indices             // Vertex and index data
    );
    pTerrainEntity;
  }


  /** 
   * Creates all Cameras present in initial Scene
   *
   *  @param  Scene*  Pointer to scene instance we're building
   *  @return void
   */
  void CreateCameras(Scene* pScene)
  {
    // Local variables used for building Scene
    Entity* pEntity;
    ScriptHandler* pScriptHander;

    /*
     * Create Camera entity
     *
     * ATTACHED COMPONENTS:
     *  Transform
     *  Camera
     */
    pEntity = pScene->CreateCamera(
      Vector3f(0.2f, 5.0f, 0.0f),        // Position
      Vector3f(0.0f, 1.0f, 0.0f),           // Start up direction
      static_cast<dfloat>(M_PI_4), static_cast<dfloat>(-(M_PI_4 / 2))   // Start yaw and pitch (radians)
    );

    // Add ScriptHanlder Component
    pScriptHander = pEntity->AddComponent<ScriptHandler>();

    // Attach new Script to it
    pScriptHander->AddScript<FirstPersonCameraController>();

    /*
     * General Input script handler
     * 
     * Provides global input on F1 - F12 keys.
     */
    {
      // Add ScriptHanlder Component that we will attach our custom Script to
      pScriptHander = pEntity->AddComponent<ScriptHandler>();

      // Attach new Script to it
      pScriptHander->AddScript<GeneralInputHandler>();
    }

    // Add DirectionalLight Component
    PointLight* pLight = pEntity->AddComponent<PointLight>();
    pLight->SetColour(glm::vec3(255.0f, 30.0f, 30.0f));
    pLight->SetInensities(glm::vec3(0.0f, 0.1f, 0.4f));
    pLight->SetShadowDimensions(glm::vec3(2048, 2048, 0), 0.01f, 100.0f);
    pLight->SetCoeficients(glm::vec3(0.02f, 0.03f, 0.04f));


    // Save all edits done on this Entity
    pEntity->SaveEntity();
  }

  /** 
   * Creates Light present in initial Scene
   *
   *  @param  Scene*  Pointer to scene instance we're building
   *  @return void
   */
  void ConstructLighting(Scene* pScene)
  {
    // Create main DirectionalLight
    pScene->CreateDirectionalLight(
      Vector3f(0.0f, 0.0f, 0.0f),          // Position vector
      Vector3f(0.0f, 0.0f, 0.0f),          // Rotation vector
      Vector3f(1.0f, 1.0f, 1.0f),          // Scale vector
      Vector3f(1.0f, 1.0f, 1.0f),          // Colour vector
      Vector3f(0.1f, 0.5f, 0.1f),          // Intensities
      Vector3u(2048, 2048, 0),             // Shadow dimensions
      Vector3f(7.0f, -5.0f, -3.0f)         // Light direction
    );

    // Create top left SpotLight
    pScene->CreateSpotLight(
      Vector3f(-8.0f, 11.0f, -4.0f),     // Position vector
      Vector3f(0.0f, 0.0f, 0.0f),        // Rotation vector
      Vector3f(1.0f, 1.0f, 1.0f),        // Scale vector
      Vector3f(1.0f, 0.0f, 1.0f),        // Colour vector
      Vector3f(0.8f, 1.0f, 1.0f),        // Intensities
      Vector3u(2048, 2048, 0),           // Shadow dimensions
      0.01f, 100.0f,                     // Near and far plane distances
      Vector3f(0.01f, 0.02f, 0.03f),     // Coefficients
      Vector3f(1.0f, -1.0f, -1.0f),      // Light direction
      35.0f                              // Cone angle (degrees)
    );
  }


};


}