#pragma once

#define SAFE_DELETE(ptr) { delete ptr; ptr = nullptr; }
#define SAFE_DELETE_ARR(ptrArr) {delete[] ptrArr; ptrArr = nullptr; }

#if PRINT_NOT_IMPLEMENTED_WARNINGS
  #define LOG_NOT_IMPLEMENTED DLog(eLogType::Warning, "NOT IMPLEMENTED function used!")
#else
  #define LOG_NOT_IMPLEMENTED
#endif

#define CONCATENATE_LITERALS(A, B) A ## B
#define CONCATENATE_DEFINES(A, B) CONCATENATE_LITERALS(A, B)

/**
 * Macros for accesing main modules from map container
 */
#define ENGINE_API static_cast<EngineApi*>(_subModules[ID_ENGINE_API].get())
#define INPUT_MANAGER static_cast<InputManager*>(_subModules[ID_INPUT_MANAGER].get())
#define ENTITY_MANAGER static_cast<EntityManager*>(_subModules[ID_ENTITY_MANAGER].get())
#define NETWORK_MANAGER static_cast<NetworkManager*>(_subModules[ID_NETWORK_MANAGER].get())
#define OUTPUT_MANAGER static_cast<OutputManager*>(_subModules[ID_OUTPUT_MANAGER].get())
#define RENDERING_MANAGER static_cast<RenderingManager*>(_subModules[ID_RENDERING_MANAGER].get())
#define SCENE_MANAGER static_cast<SceneManager*>(_subModules[ID_SCENE_MANAGER].get())
#define SIMULATE_ENGINE static_cast<SimulationManager*>(_subModules[ID_SIMULATE_ENGINE].get())
#define AUDIO_MANAGER static_cast<AudioManager*>(_subModules[ID_AUDIO_MANAGER].get())
#define COMPONENT_MANAGER static_cast<ComponentManager*>(_subModules[ID_COMPONENT_MANAGER].get())
#define WINDOW_MANAGER static_cast<WindowManager*>(_subModules[ID_WINDOW_MANAGER].get())
#define UI_MANAGER static_cast<UiManager*>(_subModules[ID_UI_MANAGER].get())

/**
 * Macros for accesing main sub-modules from map container
 */
 // RenderingManager submodules
#define KEYBOARD_MANAGER static_cast<KeyboardManager*>(_subModules[ID_KEYBOARD_MANAGER].get())
#define MOUSE_MANAGER static_cast<MouseManager*>(_subModules[ID_MOUSE_MANAGER].get())
#define COMTROLLER_MANAGER static_cast<ControllerManager*>(_subModules[ID_CONTROLLER_MANAGER].get())


// RenderingManager submodules
#define MESH_MANAGER static_cast<MeshManager*>(_subModules[ID_MESH_MANAGER].get())
#define MODEL_MANAGER static_cast<ModelManager*>(_subModules[ID_MODEL_MANAGER].get())
#define SHADER_MANAGER static_cast<EntityManager*>(_subModules[ID_SHADER_MANAGER].get())
#define SHDOW_MANAGER static_cast<NetworkManager*>(_subModules[ID_SHDOW_MANAGER].get())
#define SKYBOX_MANAGER static_cast<OutputManager*>(_subModules[ID_SKYBOX_MANAGER].get())
#define TEXTURE_MANAGER static_cast<TextureManager*>(_subModules[ID_TEXTURE_MANAGER].get())
#define SIMULATION_MANAGER static_cast<SimulationManager*>(_subModules[ID_SIMULATION_MANAGER].get())


#define AI_MANAGER static_cast<AiManager*>(_subModules[ID_AI_MANAGER].get())
#define LOGIC_MANAGER static_cast<LogicManager*>(_subModules[ID_LOGIC_MANAGER].get())
#define SCRIPT_MANAGER static_cast<ScriptManager*>(_subModules[ID_SCRIPT_MANAGER].get())
#define PHYSICS_MANAGER static_cast<PhysicsManager*>(_subModules[ID_PHYSICS_MANAGER].get())


#define MESH_GENERATOR static_cast<MeshGenerator*>(_subModules[ID_MESH_GENERATOR].get())


/**
 * Constant shortcuts.
 */
#define CONST_MESH_GENERATOR static_cast<MeshGenerator*>(_subModules.find(ID_MESH_GENERATOR)->second.get())