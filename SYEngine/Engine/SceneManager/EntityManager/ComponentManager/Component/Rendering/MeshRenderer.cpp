#include "MeshRenderer.h"

#pragma warning(push, 1)
#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#pragma warning(pop)

#include "Entity.h"
#include "Material.h"
#include "Mesh.h"
#include "Transform.h"

using namespace SYE;

SYE::MeshRenderer::MeshRenderer(
  Entity* pOwnerEntity, Component* pOwnerComponent,
  eSlotIndex slotIndex, Component::eType type
) :
  Component(
    pOwnerEntity, pOwnerComponent,
    true, true,
    slotIndex, type
  )
{}

glm::mat4 MeshRenderer::GetModelToWorldMatrix() const
{
  // Initialize identity
  glm::mat4 modelToWorldMatrix = std::move(glm::mat4(1.0f));

  // Last transform is to put everything back due to origin transform
  modelToWorldMatrix = glm::translate(modelToWorldMatrix, -(GetTransformPtr()->GetOrigin().GetData()));

  // Lastly transform
  modelToWorldMatrix = glm::translate(modelToWorldMatrix, GetTransformPtr()->GetPosition().GetData());
  // Rotate X
  modelToWorldMatrix = glm::rotate(modelToWorldMatrix, GetTransformPtr()->GetRotation().GetZ(), glm::vec3(0.0f, 0.0f, 1.0f));
  // Rotate Y
  modelToWorldMatrix = glm::rotate(modelToWorldMatrix, GetTransformPtr()->GetRotation().GetY(), glm::vec3(0.0f, 1.0f, 0.0f));
  // Rotate Z
  modelToWorldMatrix = glm::rotate(modelToWorldMatrix, GetTransformPtr()->GetRotation().GetX(), glm::vec3(1.0f, 0.0f, 0.0f));
  // Scale first
  modelToWorldMatrix = glm::scale(modelToWorldMatrix, GetTransformPtr()->GetScale().GetData());

  // Apply inverse origin translation first
  modelToWorldMatrix = glm::translate(modelToWorldMatrix, GetTransformPtr()->GetOrigin().GetData());

  return modelToWorldMatrix;
}

void MeshRenderer::Render(GLuint ul_modelToWorldMatrix, GLuint ul_specularIntensityLocation, GLuint ul_shininessIntensitLocation) const
{
  // TODO: Abstract matrices out in MathLibrary.h

  // Prepare Model->World transform matrix
  glm::mat4 modelToWorldMatrix = GetModelToWorldMatrix();
 

  glUniformMatrix4fv(ul_modelToWorldMatrix, 1, GL_FALSE, glm::value_ptr(modelToWorldMatrix));

  for (size_t i = 0; i < _meshes.size(); ++i)
  {
    // If any materials
    if (!_materials.empty())
    {
      // Apply Material
      _materials[_meshToMaterialIndex[i]]->UseMaterial(
        ul_specularIntensityLocation, ul_shininessIntensitLocation,
        0ULL // TODO: Support multiple mats in one Material instance.
      );
    }

    // Render Mesh
    _meshes[i]->RenderMesh();
  }
}

void MeshRenderer::RenderForLight(GLuint ul_modelToWorldMatrix) const
{
  // TODO: Abstract matrices out in MathLibrary.h

  // Prepare Model->World transform matrix
  glm::mat4 modelToWorldMatrix = GetModelToWorldMatrix();

  glUniformMatrix4fv(ul_modelToWorldMatrix, 1, GL_FALSE, glm::value_ptr(modelToWorldMatrix));

  for (size_t i = 0; i < _meshes.size(); ++i)
  {
     // Render Mesh
    _meshes[i]->RenderMesh();
  }
}


Mesh* MeshRenderer::AddMesh()
{
  // Create new Mesh Component
  Mesh* pMesh = GetComponentManagerPtr()->CreateComponent<Mesh>(_pOwnerEntity, this);

  // Push it in
  _meshes.push_back(pMesh);

  return pMesh;
}

Mesh* MeshRenderer::AddMesh(Mesh* pMesh)
{
  _meshes.push_back(pMesh);

  return pMesh;
}

Material* MeshRenderer::AddMaterial()
{
  // Create empty Material.
  Material* pMaterial = GetComponentManagerPtr()->CreateComponent<Material>(_pOwnerEntity, this);
  // Add default texture
  pMaterial->AddTexture();

  // Add default shininess
  pMaterial->AddShininess();
  pMaterial->AddTextureToShininessIndex(0ULL, 0ULL);

  // Add default shader
  pMaterial->AddShader();
  pMaterial->AddTextureToShaderIndex(0ULL, 0ULL);

  // Push it in
  _materials.push_back(pMaterial);

  return pMaterial;
}

Material* MeshRenderer::AddMaterial(
  Vector3f colour,
  dfloat specularIntensity, dfloat shininessIntensity
)
{
  // Create empty Material.
  Material* pMaterial = GetComponentManagerPtr()->CreateComponent<Material>(_pOwnerEntity, this);
  // Add default texture
  pMaterial->AddTexture(colour);

  // Add default shininess
  pMaterial->AddShininess(specularIntensity, shininessIntensity);
  pMaterial->AddTextureToShininessIndex(0ULL, 0ULL);

  // Add default shader
  pMaterial->AddShader();
  pMaterial->AddTextureToShaderIndex(0ULL, 0ULL);

  // Push it in
  _materials.push_back(pMaterial);

  return pMaterial;
}

Material* MeshRenderer::AddMaterial(
  std::string_view textureFilePath,
  dfloat specularIntensity, dfloat shininessIntensity,
  std::string_view shaderPathFile
)
{
  // Create empty Material.
  Material* pMaterial = GetComponentManagerPtr()->CreateComponent<Material>(_pOwnerEntity, this);
  // Add texture
  pMaterial->AddTexture(textureFilePath);

  // Add default shininess
  pMaterial->AddShininess(specularIntensity, shininessIntensity);
  pMaterial->AddTextureToShininessIndex(0ULL, 0ULL);

  // Add default shader
  pMaterial->AddShader(shaderPathFile);
  pMaterial->AddTextureToShaderIndex(0ULL, 0ULL);

  // Push it in
  _materials.push_back(pMaterial);

  return pMaterial;
}

Material* MeshRenderer::AddMaterial(Texture* pTexture, Shininess* pShininess, Shader* pShader)
{
  Material* pMaterial = GetComponentManagerPtr()->CreateComponent<Material>(_pOwnerEntity, this);
  pMaterial->AddTexture(pTexture);
  pMaterial->AddShininess(pShininess);
  pMaterial->AddShader(pShader);
  pMaterial->AddTextureToShininessIndex(0ULL, 0ULL);

  // Push it in
  _materials.push_back(pMaterial);

  return pMaterial;
}

bool MeshRenderer::AddMeshToMaterialIndex(size_t meshIndex, size_t materialIndex)
{
  // If out of existing meshes and materials range
  if (meshIndex >= _meshes.size() || meshIndex >= _materials.size())
  {
    PUSH_EDITOR_ERROR(
      eEngineError::OutOfRangeIndices,
      "Provided indices " + std::to_string(meshIndex) +  ", " + std::to_string(materialIndex) + " are out of bound for existing meshes and materials.", 
      ""
    );

    return false;
  }

  _meshToMaterialIndex.resize(meshIndex + 1);
  _meshToMaterialIndex[meshIndex] = materialIndex;

  return true;
}

void MeshRenderer::ClearAll()
{
  _meshes.clear();
  _materials.clear();
  _meshToMaterialIndex.clear();
}

void MeshRenderer::ClearMaterials()
{
  for (auto&& material : _materials)
  {
    GetComponentManagerPtr()->DestroyComponent(material);
  }
  _materials.clear();
}
