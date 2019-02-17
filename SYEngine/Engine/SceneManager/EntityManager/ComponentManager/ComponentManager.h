#pragma once

#include <map>
#include <memory>

#pragma warning(push, 1)
#include <glm/glm.hpp>
#pragma warning(pop)

#include "common.h"
#include "BaseModule.h"
#include "Component.h"

namespace SYE 
{

class Component;
class Entity;

#if !NEW_SSSEC_IMPLEMENTED
class TextureManager;
class Mesh;
class Texture;
class _Shininess;
#endif

class ComponentManager:
    public BaseModule
{
public:
  ComponentManager() = delete;

  ComponentManager(BaseModule& parentModule);
  ~ComponentManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  template <typename ComponentType>
  ComponentType* CreateComponent(Entity* pOwnerEntity)
  {
    // Instantiate new Component
    return InsertComponent<ComponentType>(std::make_unique<ComponentType>(pOwnerEntity, _subModules));
  }

  /** 
   * Destructs Component instance that provided pointer points to.
   *
   * @param Component*  Pointer to instance to destroy.
   * @return  bool  True if destroyed, false if there was nothing to destroy.
   */
  bool RemoveComponent(Component* pComponentToRemove)
  {
    if (pComponentToRemove == nullptr)
    {
      return false;
    }

    auto result = _components.erase(pComponentToRemove->GetGuid());

    if (result < 1)
    {
      return false;
    }

    return true;
  }
 
private:
  template <typename ComponentType>
  ComponentType* InsertComponent(std::unique_ptr<ComponentType>&& pNewComponent)
  {
    auto result = _components.insert(std::make_pair(pNewComponent->GetGuid(), std::move(pNewComponent)));

    return static_cast<ComponentType*>(result.first->second.get());
  }


private:
  /** Owner list of all components that exist */
  std::map<size_t, std::unique_ptr<Component>> _components;

#if !NEW_SSSEC_IMPLEMENTED

  

public:
  std::unique_ptr<Mesh> GenerateMeshQuad(dfloat width, dfloat height);
  std::unique_ptr<Mesh> GenerateMeshBlock(dfloat width, dfloat height, dfloat length);

  Component* CreateBoxCollider(
    Entity* pEntity,
    glm::vec3 position, glm::vec3 rotation, glm::vec3 scale,
    dfloat width,
    dfloat heigt,
    dfloat length,
    bool bIsStatic
  );

  Component* CreateModel(
    Entity* pEntity,
    std::unique_ptr<Mesh>&& pQuadMesh,
    std::unique_ptr<Texture>&& pTexture = nullptr,
    std::unique_ptr<_Shininess>&& pShininess = nullptr
  );

  Component* CreateModelFromFile(
    Entity* pEntity,
    std::string_view filePath
  );


  TextureManager* GetTextureManager() const { return _pTextureManager;  }

  TextureManager* _pTextureManager;

#endif
};

} // namespace SYE