#pragma once

#include <vector>

#include <GL/glew.h>

#include "Component.h"

namespace SYE 
{

class Material;
class Mesh;
class Shader;
class Shininess;
class Texture;

class MeshRenderer:
  public Component
{
public:
  MeshRenderer() = delete;
  MeshRenderer(Entity* pOwnerEntity, const std::map< int, std::unique_ptr<BaseModule> >& subModulesConstRef);
  ~MeshRenderer();

  void Render(GLuint ul_modelToWorldMatrix, GLuint ul_specularIntensityLocation, GLuint ul_shininessIntensitLocation) const;
  void RenderForLight(GLuint ul_modelToWorldMatrix) const;

  /**
   * Attaches default Mesh to this MeshRender
   *
   * Default Mesh is empty - no vertices nor indices.
   */
  Mesh* AddMesh();

  /**
   * Attaches provided Mesh to MeshRenderer.
   */
  Mesh* AddMesh(Mesh* pMesh);

  /**
   * Attaches default Material to this MeshRender
   *
   * Default Material is default texture with dull Shininess.
   */
  Material* AddMaterial();
  
  /**
   * Attaches new material with specified properties
   *
   * @param   std::string_view  Filepath to texture file.
   * @param   dfloat            Intensity for specular reflections.
   *                              E.g: shiny: 1.0f, dull: 0.3f 
   * @param   dfloat            Shinines factor.
   *                              E.g: shiny: 512 dull: 4
   * @param   std::string_view  Filepath to shader file.
   */
  Material* AddMaterial(
    std::string_view textureFilePath, 
    dfloat specularIntensity, dfloat shininessIntensity, 
    std::string_view shaderPathFile
  );

  /**
   * Attaches new Material consisting of provided parts
   */
  Material* AddMaterial(Texture* pTexture, Shininess* pShininess, Shader* pShader);
  bool AddMeshToMaterialIndex(size_t meshIndex, size_t materialIndex);

  void ClearAll();

protected:
  std::vector<Mesh*> _meshes;
  std::vector<Material*> _materials;
  std::vector<size_t> _meshToMaterialIndex;

};

}