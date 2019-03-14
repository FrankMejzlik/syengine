
#include "IEngineContextInterface.h"

// Include all implemented classes
#include "EngineApi.h"
#include "InputManager.h"
#include "EntityManager.h"
#include "NetworkManager.h"
#include "OutputManager.h"
#include "RenderingManager.h"
#include "SceneManager.h"
#include "SimulationManager.h"
#include "AudioManager.h"
#include "ComponentManager.h"
#include "KeyboardManager.h"
#include "MouseManager.h"
#include "PhysicsManager.h"
#include "MaterialManager.h"
#include "MeshManager.h"
#include "ShaderManager.h"
#include "SkyboxManager.h"
#include "TextureManager.h"
#include "WindowManager.h"
#include "ModelManager.h"
#include "UiManager.h"
#include "AiManager.h"
#include "ScriptManager.h"



IEngineContextInterface::IEngineContextInterface(EngineContext* pEngineContext):
  _pEngineContext(pEngineContext)
{}

EngineContext* IEngineContextInterface::GetEngineContextPtr() const
{
  return _pEngineContext;
};

EngineApi*  IEngineContextInterface::GetEngineApiPtr() const 
{ 
  return static_cast<EngineApi*>(_pEngineContext->GetModule(ID_ENGINE_API));
} 

InputManager*  IEngineContextInterface::GetInputManagerPtr() const 
{ 
  return static_cast<InputManager*>(_pEngineContext->GetModule(ID_INPUT_MANAGER));
} 

EntityManager*  IEngineContextInterface::GetEntityManagerPtr() const 
{ 
  return static_cast<EntityManager*>(_pEngineContext->GetModule(ID_ENTITY_MANAGER));
} 

NetworkManager*  IEngineContextInterface::GetNetworkManagerPtr() const 
{ 
  return static_cast<NetworkManager*>(_pEngineContext->GetModule(ID_NETWORK_MANAGER));
} 

OutputManager*  IEngineContextInterface::GetOutputManagerPtr() const 
 { 
  return static_cast<OutputManager*>(_pEngineContext->GetModule(ID_OUTPUT_MANAGER));
} 

RenderingManager*  IEngineContextInterface::GetRenderingManagerPtr() const 
 { 
  return static_cast<RenderingManager*>(_pEngineContext->GetModule(ID_RENDERING_MANAGER));
} 

SceneManager*  IEngineContextInterface::GetSceneManagerPtr() const 
 { 
  return static_cast<SceneManager*>(_pEngineContext->GetModule(ID_SCENE_MANAGER));
} 

SimulationManager*  IEngineContextInterface::GetSimulationManagerPtr() const 
 { 
  return static_cast<SimulationManager*>(_pEngineContext->GetModule(ID_SIMULATION_MANAGER));
} 

AudioManager*  IEngineContextInterface::GetAudioManagerPtr() const 
 { 
  return static_cast<AudioManager*>(_pEngineContext->GetModule(ID_AUDIO_MANAGER));
} 

ComponentManager*  IEngineContextInterface::GetComponentManagerPtr() const 
 { 
  return static_cast<ComponentManager*>(_pEngineContext->GetModule(ID_COMPONENT_MANAGER));
} 

KeyboardManager*  IEngineContextInterface::GetKeyboardManagerPtr() const 
 { 
  return static_cast<KeyboardManager*>(_pEngineContext->GetModule(ID_KEYBOARD_MANAGER));
} 

MouseManager*  IEngineContextInterface::GetMouseManagerPtr() const 
 { 
  return static_cast<MouseManager*>(_pEngineContext->GetModule(ID_MOUSE_MANAGER));
} 

PhysicsManager*  IEngineContextInterface::GetPhysicsManagerPtr() const 
 { 
  return static_cast<PhysicsManager*>(_pEngineContext->GetModule(ID_PHYSICS_MANAGER));
} 

MaterialManager*  IEngineContextInterface::GetMaterialManagerPtr() const 
 { 
  return static_cast<MaterialManager*>(_pEngineContext->GetModule(ID_MATERIAL_MANAGER));
} 

MeshManager*  IEngineContextInterface::GetMeshManagerPtr() const 
 { 
  return static_cast<MeshManager*>(_pEngineContext->GetModule(ID_MESH_MANAGER));
} 

ShaderManager*  IEngineContextInterface::GetShaderManagerPtr() const 
 { 
  return static_cast<ShaderManager*>(_pEngineContext->GetModule(ID_SHADER_MANAGER));
} 

SkyboxManager*  IEngineContextInterface::GetSkyboxManagerPtr() const 
 { 
  return static_cast<SkyboxManager*>(_pEngineContext->GetModule(ID_SKYBOX_MANAGER));
} 

TextureManager*  IEngineContextInterface::GetTextureManagerPtr() const 
 { 
  return static_cast<TextureManager*>(_pEngineContext->GetModule(ID_TEXTURE_MANAGER));
} 

WindowManager*  IEngineContextInterface::GetWindowManagerPtr() const 
 { 
  return static_cast<WindowManager*>(_pEngineContext->GetModule(ID_WINDOW_MANAGER));
} 

ModelManager*  IEngineContextInterface::GetModelManagerPtr() const 
 { 
  return static_cast<ModelManager*>(_pEngineContext->GetModule(ID_MODEL_MANAGER));
} 

UiManager*  IEngineContextInterface::GetUiManagerPtr() const 
 { 
  return static_cast<UiManager*>(_pEngineContext->GetModule(ID_UI_MANAGER));
} 

AiManager*  IEngineContextInterface::GetAiManagerPtr() const 
 { 
  return static_cast<AiManager*>(_pEngineContext->GetModule(ID_AI_MANAGER));
} 

ScriptManager*  IEngineContextInterface::GetScriptManagerPtr() const 
 { 
  return static_cast<ScriptManager*>(_pEngineContext->GetModule(ID_SCRIPT_MANAGER));
} 
