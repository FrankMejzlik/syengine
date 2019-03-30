#pragma once

namespace SYE 
{

// Forward declarations
class EngineContext;
class EngineApi;
class InputManager;
class EntityManager;
class NetworkManager;
class OutputManager;
class RenderingManager;
class SceneManager;
class SimulationManager;
class AudioManager;
class ComponentManager;
class KeyboardManager;
class MouseManager;
class PhysicsManager;
class MaterialManager;
class MeshManager;
class ShaderManager;
class ShadowManager;
class SkyboxManager;
class TextureManager;
class WindowManager;
class ModelManager;
class UiManager;
class ScriptManager;


/**
 * Interface for classes that needs to access EngineContext data
 *
 * This class is NOT responsible for allocation, only provides common API to it.
 */
class IEngineContextInterface
{
public:
  IEngineContextInterface() = delete;
  IEngineContextInterface(EngineContext* pEngineContext);

  EngineContext* GetEngineContextPtr() const;

  /** Module getters */
  EngineApi* GetEngineApiPtr() const;
  InputManager* GetInputManagerPtr() const;
  EntityManager* GetEntityManagerPtr() const;
  NetworkManager* GetNetworkManagerPtr() const;
  OutputManager* GetOutputManagerPtr() const;
  RenderingManager* GetRenderingManagerPtr() const;
  SceneManager* GetSceneManagerPtr() const;
  SimulationManager* GetSimulationManagerPtr() const;
  AudioManager* GetAudioManagerPtr() const;
  ComponentManager* GetComponentManagerPtr() const;
  KeyboardManager* GetKeyboardManagerPtr() const;
  MouseManager* GetMouseManagerPtr() const;
  PhysicsManager* GetPhysicsManagerPtr() const;
  MaterialManager* GetMaterialManagerPtr() const;
  MeshManager* GetMeshManagerPtr() const;
  ShaderManager* GetShaderManagerPtr() const;
  SkyboxManager* GetSkyboxManagerPtr() const;
  TextureManager* GetTextureManagerPtr() const;
  WindowManager* GetWindowManagerPtr() const;
  ModelManager* GetModelManagerPtr() const;
  UiManager* GetUiManagerPtr() const;
  ScriptManager* GetScriptManagerPtr() const;

private:
  /** Context of Engine instance */
  EngineContext* _pEngineContext;

};

}
