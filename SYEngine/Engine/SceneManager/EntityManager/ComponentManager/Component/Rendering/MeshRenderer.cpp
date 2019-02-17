#include "MeshRenderer.h"

#pragma warning(push, 1)
#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#pragma warning(pop)

#include "Entity.h"
#include "Material_.h"
#include "Mesh.h"
#include "Transform.h"

using namespace SYE;

SYE::MeshRenderer::MeshRenderer(Entity * pOwnerEntity, const std::map<int, std::unique_ptr<BaseModule>>& subModulesConstRef) :
  Component(
    pOwnerEntity, subModulesConstRef,
    true, true,
    MESH_RENDERER
  )
{
  _type = eType::MESH_RENDERER;
}

MeshRenderer::~MeshRenderer()
{}

void MeshRenderer::Render(GLuint ul_modelToWorldMatrix, GLuint ul_specularIntensityLocation, GLuint ul_shininessIntensitLocation) const
{
  // TODO: Abstract matrices out in MathLibrary.h

  // Prepare Model->World transform matrix
  glm::mat4 modelToWorldMatrix;
  modelToWorldMatrix = std::move(glm::mat4(1.0f));
  modelToWorldMatrix = glm::translate(modelToWorldMatrix, _pOwnerEntity->GetTransform()->GetPosition().GetData());
  modelToWorldMatrix = glm::rotate(modelToWorldMatrix, _pOwnerEntity->GetTransform()->GetRotation().GetZ(), glm::vec3(0.0f, 0.0f, 1.0f));
  modelToWorldMatrix = glm::rotate(modelToWorldMatrix, _pOwnerEntity->GetTransform()->GetRotation().GetY(), glm::vec3(0.0f, 1.0f, 0.0f));
  modelToWorldMatrix = glm::rotate(modelToWorldMatrix, _pOwnerEntity->GetTransform()->GetRotation().GetX(), glm::vec3(1.0f, 0.0f, 0.0f));
  modelToWorldMatrix = glm::scale(modelToWorldMatrix, _pOwnerEntity->GetTransform()->GetScale().GetData());

  glUniformMatrix4fv(ul_modelToWorldMatrix, 1, GL_FALSE, glm::value_ptr(modelToWorldMatrix));

  for (size_t i = 0; i < _meshes.size(); ++i)
  {
    // Apply Material
    _materials[_meshToMaterialIndex[i]]->UseMaterial(
      ul_specularIntensityLocation, ul_shininessIntensitLocation,
      0ULL, 0ULL // TODO: Support multiple mats in one Material instance.
    );

    // Render Mesh
    _meshes[i]->RenderMesh();
  }
}


Mesh* MeshRenderer::AddMesh()
{
  // Create new Mesh Component
  Mesh* pMesh = _pComponentManager->CreateComponent<Mesh>(_pOwnerEntity);

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
  Material* pMaterial = _pComponentManager->CreateComponent<Material>(_pOwnerEntity);
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
  std::string_view textureFilePath,
  dfloat specularIntensity, dfloat shininessIntensity,
  std::string_view shaderPathFile
)
{
  // Create empty Material.
  Material* pMaterial = _pComponentManager->CreateComponent<Material>(_pOwnerEntity);
  // Add texture
  pMaterial->AddTexture(textureFilePath);

  // Add default shininess
  pMaterial->AddShininess(specularIntensity, shininessIntensity);
  pMaterial->AddTextureToShininessIndex(0ULL, 0ULL);

  // Add default shader
  pMaterial->AddShader(shaderPathFile);
  pMaterial->AddTextureToShaderIndex(0ULL, 0ULL);

  // Set is as custom
  pMaterial->SetIsDefault(false);

  // Push it in
  _materials.push_back(pMaterial);

  return pMaterial;
}

Material* MeshRenderer::AddMaterial(Texture* pTexture, Shininess* pShininess, Shader* pShader)
{
  Material* pMaterial = _pComponentManager->CreateComponent<Material>(_pOwnerEntity);
  pMaterial->AddTexture(pTexture);
  pMaterial->AddShininess(pShininess);
  pMaterial->AddShader(pShader);
  pMaterial->AddTextureToShininessIndex(0ULL, 0ULL);

  // Set is as custom
  pMaterial->SetIsDefault(false);

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
