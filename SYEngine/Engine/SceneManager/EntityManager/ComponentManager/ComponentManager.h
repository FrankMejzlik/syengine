#pragma once

#include <map>
#include <memory>

#pragma warning(push, 1)
#include <glm/glm.hpp>
#pragma warning(pop)

#include "common.h"
#include "BaseModule.h"
#include "Component.h"
#include "Entity.h"

namespace SYE 
{

class Component;


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
    return InsertComponent<ComponentType>(std::make_unique<ComponentType>(pOwnerEntity, _subModules, pOwnerEntity->GetPrimaryComponentSlotsRef()));
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
};

} // namespace SYE