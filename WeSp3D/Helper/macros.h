#pragma once

#define SAFE_DELETE(ptr) { delete ptr; ptr = nullptr; }
#define SAFE_DELETE_ARR(ptrArr) {delete[] ptrArr; ptrArr = nullptr; }


#define PARENT_ENGINE std::static_cast<Engine&>(_parentModule)

/**
 * Macros for accesing main modules from map container
 */
#define ENGINE_API std::static_pointer_cast<EngineApi>(_subModules[ID_ENGINE_API])
#define INPUT_MANAGER std::static_pointer_cast<InputManager>(_subModules[ID_INPUT_MANAGER])
#define ENTITY_MANAGER std::static_pointer_cast<EntityManager>(_subModules[ID_ENTITY_MANAGER])
#define NETWORK_MANAGER std::static_pointer_cast<NetworkManager>(_subModules[ID_NETWORK_MANAGER])
#define OUTPUT_MANAGER std::static_pointer_cast<OutputManager>(_subModules[ID_OUTPUT_MANAGER])
#define RENDERING_MANAGER std::static_pointer_cast<RenderingManager>(_subModules[ID_RENDERING_MANAGER])
#define SCENE_MANAGER std::static_pointer_cast<SceneManager>(_subModules[ID_SCENE_MANAGER])
#define SIMULATE_ENGINE std::static_pointer_cast<SimulationManager>(_subModules[ID_SIMULATE_ENGINE])
#define AUDIO_MANAGER std::static_pointer_cast<AudioManager>(_subModules[ID_AUDIO_MANAGER])
#define COMPONENT_MANAGER std::static_pointer_cast<ComponentManager>(_subModules[ID_COMPONENT_MANAGER])

/**
 * Macros for accesing main sub-modules from map container
 */
 // RenderingManager submodules
#define KEYBOARD_MANAGER std::static_pointer_cast<KeyboardManager>(_subModules[ID_KEYBOARD_MANAGER])
#define MOUSE_MANAGER std::static_pointer_cast<MouseManager>(_subModules[ID_MOUSE_MANAGER])
#define COMTROLLER_MANAGER std::static_pointer_cast<ControllerManager>(_subModules[ID_CONTROLLER_MANAGER])


// RenderingManager submodules
#define MESH_MANAGER std::static_pointer_cast<EngineApi>(_subModules[ID_MESH_MANAGER])
#define MODEL_MANAGER std::static_pointer_cast<InputManager>(_subModules[ID_MODEL_MANAGER])
#define SHADER_MANAGER std::static_pointer_cast<EntityManager>(_subModules[ID_SHADER_MANAGER])
#define SHDOW_MANAGER std::static_pointer_cast<NetworkManager>(_subModules[ID_SHDOW_MANAGER])
#define SKYBOX_MANAGER std::static_pointer_cast<OutputManager>(_subModules[ID_SKYBOX_MANAGER])
#define TEXTURE_MANAGER std::static_pointer_cast<RenderingManager>(_subModules[ID_TEXTURE_MANAGER])


// SimulationManager submodules
#define AI_MANAGER std::static_pointer_cast<AIManager>(_subModules[ID_AI_MANAGER])
#define LOGIC_MANAGER std::static_pointer_cast<LogicManager>(_subModules[ID_LOGIC_MANAGER])
#define PHYSICS_MANAGER std::static_pointer_cast<PhysicsManager>(_subModules[ID_PHYSICS_MANAGER])


