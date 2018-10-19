#pragma once

#define SAFE_DELETE(ptr) { delete ptr; ptr = nullptr; }
#define SAFE_DELETE_ARR(ptrArr) {delete[] ptrArr; ptrArr = nullptr; }

/**
 * Macros for accesing main modules from map container
 */
#define ENGINE_API std::static_pointer_cast<EngineAPI>(_modules[ID_ENGINE_API])
#define INPUT_MANAGER std::static_pointer_cast<InputManager>(_modules[ID_INPUT_MANAGER])
#define ENTITY_MANAGER std::static_pointer_cast<EntityManager>(_modules[ID_ENTITY_MANAGER])
#define NETWORK_MANAGER std::static_pointer_cast<NetworkManager>(_modules[ID_NETWORK_MANAGER])
#define OUTPUT_MANAGER std::static_pointer_cast<OutputManager>(_modules[ID_OUTPUT_MANAGER])
#define RENDERING_MANAGER std::static_pointer_cast<RenderingManager>(_modules[ID_RENDERING_MANAGER])
#define SCENE_MANAGER std::static_pointer_cast<SceneManager>(_modules[ID_SCENE_MANAGER])
#define SIMULATE_ENGINE std::static_pointer_cast<SimulationManager>(_modules[ID_SIMULATE_ENGINE])
#define AUDIO_MANAGER std::static_pointer_cast<AudioManager>(_modules[ID_AUDIO_MANAGER])
#define COMPONENT_MANAGER std::static_pointer_cast<ComponentManager>(_modules[ID_COMPONENT_MANAGER])

/**
 * Macros for accesing main sub-modules from map container
 */
 // RenderingManager submodules
#define KEYBOARD_MANAGER std::static_pointer_cast<KeyboardManager>(_modules[ID_KEYBOARD_MANAGER])
#define MOUSE_MANAGER std::static_pointer_cast<MouseManager>(_modules[ID_MOUSE_MANAGER])
#define COMTROLLER_MANAGER std::static_pointer_cast<ControllerManager>(_modules[ID_CONTROLLER_MANAGER])


// RenderingManager submodules
#define MESH_MANAGER std::static_pointer_cast<EngineAPI>(_modules[ID_MESH_MANAGER])
#define MODEL_MANAGER std::static_pointer_cast<InputManager>(_modules[ID_MODEL_MANAGER])
#define SHADER_MANAGER std::static_pointer_cast<EntityManager>(_modules[ID_SHADER_MANAGER])
#define SHDOW_MANAGER std::static_pointer_cast<NetworkManager>(_modules[ID_SHDOW_MANAGER])
#define SKYBOX_MANAGER std::static_pointer_cast<OutputManager>(_modules[ID_SKYBOX_MANAGER])
#define TEXTURE_MANAGER std::static_pointer_cast<RenderingManager>(_modules[ID_TEXTURE_MANAGER])


// SimulationManager submodules
#define AI_MANAGER std::static_pointer_cast<AIManager>(_modules[ID_AI_MANAGER])
#define LOGIC_MANAGER std::static_pointer_cast<LogicManager>(_modules[ID_LOGIC_MANAGER])
#define PHYSICS_MANAGER std::static_pointer_cast<PhysicsManager>(_modules[ID_PHYSICS_MANAGER])


