#pragma once

//
#define DEV 1
#define USING_EDITOR 1
#define RELEASE 0
#define ALPHA 0
#define BETA 0
#define LOG_DEV 1
#define RUN_ENGINE_API 1

// Main modules IDs
#define ID_ENGINE_API 100
#define ID_INPUT_MANAGER 1
#define ID_ENTITY_MANAGER 2
#define ID_NETWORK_MANAGER 3
#define ID_OUTPUT_MANAGER 4
#define ID_RENDERING_MANAGER 5
#define ID_SCENE_MANAGER 6
#define ID_SIMULATION_MANAGER 7
#define ID_AUDIO_MANAGER 8
#define ID_COMPONENT_MANAGER 9

/**
 * Main sub-modules IDs
 */
 // InputManager
#define ID_KEYBOARD_MANAGER 11
#define ID_MOUSE_MANAGER 12
#define ID_CONTROLLER_MANAGER 13

 // RenderingManager

#define ID_ANIMATION_MANAGER 51
#define ID_MATERIAL_MANAGER 52
#define ID_MESH_MANAGER 53
#define ID_SHADER_MANAGER 54
#define ID_SHADOW_MANAGER 55
#define ID_SKYBOX_MANAGER 56
#define ID_TEXTURE_MANAGER 57
#define ID_WINDOW_MANAGER 58
#define ID_MODEL_MANAGER 59

// SimulationManager
#define ID_AI_MANAGER 71
#define ID_LOGIC_MANAGER 72
#define ID_PHYSICS_MANAGER 73


// Game window settings
#define GAME_WINDOW_TITLE "WeSp3D Game Preview"
#define GAME_WINDOW_DEFAULT_WIDTH 1333
#define GAME_WINDOW_DEFAULT_HEIGHT 768

#define GAME_WINDOW_DEFAULT_POS_X 588
#define GAME_WINDOW_DEFAULT_POS_Y 30

#define MAX_POINT_LIGHTS 3
#define MAX_SPOT_LIGHTS 3

#define MAGIC_BASE_MODULE_NUMBER 42

enum class eModuleState
{
  Null,
  Working,
  Idle,
  Error
};
