
#include "IComponentsInterface.h"

#include "Transform.h"
#include "PhysicsBody.h"
#include "Rigidbody.h"
#include "Softbody.h"
#include "MeshRenderer.h"
#include "PointLight.h"
#include "ScriptHandler.h"
#include "SpotLight.h"

using namespace SYE;

IComponentsInterface::IComponentsInterface(std::array< std::map<size_t, Component*>, COMPONENTS_NUM_SLOTS>& primaryComponentOnEntity) :
  _primaryComponentOnEntity(primaryComponentOnEntity)
{}


void IComponentsInterface::RefreshQuickRefs()
{
  // Update all Component type quick refs

  if (!_primaryComponentOnEntity[COMPONENT_TRANSFORM_SLOT].empty())
  {
    _pTransform = static_cast<Transform*>(_primaryComponentOnEntity[COMPONENT_TRANSFORM_SLOT].begin()->second);
  }

  if (!_primaryComponentOnEntity[COMPONENT_PHYSICS_BODY_SLOT].empty())
  {
    _pPhysicsBody = static_cast<PhysicsBody*>(_primaryComponentOnEntity[COMPONENT_PHYSICS_BODY_SLOT].begin()->second);
  }

  if (!_primaryComponentOnEntity[COMPONENT_MESH_RENDERER_SLOT].empty())
  {
    _pMeshRenderer = static_cast<MeshRenderer*>(_primaryComponentOnEntity[COMPONENT_MESH_RENDERER_SLOT].begin()->second);
  }

  if (!_primaryComponentOnEntity[COMPONENT_POINT_LIGHT_SOURCE_SLOT].empty())
  {
    _pPointLight = static_cast<PointLight*>(_primaryComponentOnEntity[COMPONENT_POINT_LIGHT_SOURCE_SLOT].begin()->second);
  }

  if (!_primaryComponentOnEntity[COMPONENT_SPOT_LIGHT_SOURCE_SLOT].empty())
  {
	  _pSpotLight = static_cast<SpotLight*>(_primaryComponentOnEntity[COMPONENT_SPOT_LIGHT_SOURCE_SLOT].begin()->second);
  }

  if (!_primaryComponentOnEntity[COMPONENT_SCRIPT_HANDLER_SLOT].empty())
  {
    _pScriptHandlers = _primaryComponentOnEntity[COMPONENT_SCRIPT_HANDLER_SLOT];
  }
}

Transform* IComponentsInterface::GetTransformPtr() const
{
  return _pTransform;
}

PhysicsBody* IComponentsInterface::GetPhysicsBody() const
{
  return _pPhysicsBody;
}

Rigidbody* IComponentsInterface::GetRigidbodyPtr() const
{
  return dynamic_cast<Rigidbody*>(_pPhysicsBody);
}

Softbody* IComponentsInterface::GetSoftbodyPtr() const
{
  return dynamic_cast<Softbody*>(_pPhysicsBody);
}

MeshRenderer* IComponentsInterface::GetMeshRendererPtr() const
{
  return _pMeshRenderer;
}

PointLight* IComponentsInterface::GetPointLightPtr() const
{
  return _pPointLight;
}

SpotLight* IComponentsInterface::GetSpotLightPtr() const
{
	return _pSpotLight;
}

ScriptHandler* IComponentsInterface::GetFirstScriptHandlerPtr() const
{
  // Return just ptr to first element, if exists
  auto it = _pScriptHandlers.begin();

  // If not fouund
  if (it == _pScriptHandlers.end())
  {
    return nullptr;
  }

  return static_cast<ScriptHandler*>(it->second);
}

std::map<size_t, Component*>& IComponentsInterface::GetScriptHandlersRef()
{
  return _pScriptHandlers;
}