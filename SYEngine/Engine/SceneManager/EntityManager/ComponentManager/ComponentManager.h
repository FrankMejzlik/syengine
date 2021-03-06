#pragma once

#include <map>
#include <memory>

#pragma warning(push, 1)
#include <GLM/glm.hpp>
#pragma warning(pop)

#include "common.h"
#include "BaseModule.h"
#include "Component.h"

namespace SYE 
{

class Component;
class Entity;

class ComponentManager:
    public BaseModule
{
public:
  ComponentManager() = delete;

  ComponentManager(BaseModule& parentModule, EngineContext* pEngineContext);
  ~ComponentManager();

  virtual bool Initialize() override;
  virtual bool Terminate() override;

  void DestroyAllComponents();

  template <typename ComponentType>
  ComponentType* CreateComponent(Entity* pOwnerEntity, Component* pOwnerComponent = nullptr)
  {
    // Instantiate new Component
    std::unique_ptr<ComponentType> pComponent = std::make_unique<ComponentType>(pOwnerEntity, pOwnerComponent);

    // If subcomponent
    if (!pComponent->IsPrimary())
    {
      //assert(pOwnerComponent != nullptr);
    }

    return InsertComponent<ComponentType>(std::move(pComponent));
  }

  std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& GetPrimaryComponentSlotsRef(Entity* pEntity);

  /** 
   * Destructs Component instance that provided pointer points to.
   *
   * @param Component*  Pointer to instance to destroy.
   * @return  bool  True if destroyed, false if there was nothing to destroy.
   */
  bool DestroyComponent(Component* pComponentToRemove)
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
};

} // namespace SYE
