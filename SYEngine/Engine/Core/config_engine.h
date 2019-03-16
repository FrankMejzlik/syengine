#pragma once

#include <stdint.h>

//////////////////////////////////////////
// Temporary
//////////////////////////////////////////
#define NEW_SHADOW_MAPPING_IMPLEMENTED 0

//////////////////////////////////////////
// Paths configuration
//////////////////////////////////////////
#define PATH_TEXTURES "resource/textures"
#define FILENAME_DEFAULT_TEXTURE "/plain.png"
#define FILEPATH_DEFAULT_TEXTURE "resource/textures/plain.png"


//////////////////////////////////////////
// Project configuration switches
//////////////////////////////////////////

//! If development version
#define DEV 1

//! If there is Editor attached to engine
#define USING_EDITOR 1

//! If Realease version
#define RELEASE 0

//! If Realease candidate version
#define RELEASE_CANDIDATE 0

//! If Alpha version
#define ALPHA 0

//! If Beta version
#define BETA 0


//////////////////////////////////////////
// PLatform configuration
//////////////////////////////////////////

//! If target is OS based on UNIX.
#if __unix__
  #define TARGET_UNIX 1
#endif

//! If target is 32/64-bit Windows OS.
#if _WIN32
  #define TARGET_WINDOWS 1
#endif


//////////////////////////////////////////
// Logging configuration
//////////////////////////////////////////
#define PRINT_NOT_IMPLEMENTED_WARNINGS 0
#define LOG_PHYSICS_MANAGER_COLLISION_MESH_CONSTRUCTION 0
#define LOG_PHYSICS_MANAGER_COLLISIONS 0
#define LOG_DEV 1
#define RUN_ENGINE_API 1

//////////////////////////////////////////
// General settings
//////////////////////////////////////////

//! If using double precision floating point types in whole project
#define USE_DOUBLES 0

//! This value will be used as error value with size_t type
#define SIZE_T_ERROR_VALUE SIZE_MAX

//! Constant to conver from degrees to radians
#define DEG_TO_RAD (3.14159265 / 180.0f)


//////////////////////////////////////////
// EngineAPI settings
//////////////////////////////////////////

//! If EngineAPI methods will be exported in DLL
#define EXPORT_ENGINE_API 0

//! If want to run tests on EngineAPI exported methods
#define TEST_EXPORTED_FUNCTIONS 0

//! Calling convention that will be used on exported methods
#define API_EXPORT_CALL_CONVENTION _stdcall


//////////////////////////////////////////
// System Entities config
//////////////////////////////////////////

#define NUM_RENDER_TARGET_TEXTURES 1

#define NUM_SYSTEM_ENTITIES 1
#define RENDER_ONTO_ENTITY 0ULL
#define RENDER_ONTO_ENTITY_WIDTH 3.0f
#define RENDER_ONTO_ENTITY_HEIGHT 3.0f

#define RENDER_TO_TEXTURE_WIDTH 500ULL
#define RENDER_TO_TEXTURE_HEIGHT 500ULL


//////////////////////////////////////////
// Shader settings
//////////////////////////////////////////

//////////////////////////////////////////
// Graphics settings
//////////////////////////////////////////
#define RENDER_SCENE_TO_TEXTUE 0

#define DISABLE_OMNI_SHADOW_MAPPING 0

#define LIGHTS_NEAR_PLANE 0.1f
#define LIGHTS_FAR_PLANE 100.0f

#define MAX_POINT_LIGHTS 3
#define MAX_SPOT_LIGHTS 3
#define MAX_DIRECTIONAL_LIGHTS 1

#define DEFAULT_SHADOW_MAP_DIMENSIONS 512

#define BACK_FACE_CULLING 1
#define DISABLE_VSYNC 0


//////////////////////////////////////////
// Module IDs
//////////////////////////////////////////
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
#define ID_KEYBOARD_MANAGER 11
#define ID_MOUSE_MANAGER 12
#define ID_CONTROLLER_MANAGER 13
#define ID_ANIMATION_MANAGER 51
#define ID_MATERIAL_MANAGER 52
#define ID_MESH_MANAGER 53
#define ID_SHADER_MANAGER 54
#define ID_SKYBOX_MANAGER 56
#define ID_TEXTURE_MANAGER 57
#define ID_WINDOW_MANAGER 58
#define ID_MODEL_MANAGER 59
#define ID_UI_MANAGER 60
#define ID_LOGIC_MANAGER 70
#define ID_AI_MANAGER 71
#define ID_PHYSICS_MANAGER 73
#define ID_SCRIPT_MANAGER 74
#define ID_MESH_GENERATOR 74


//////////////////////////////////////////
// Main window settings
//////////////////////////////////////////
#define GAME_WINDOW_TITLE "SYEngine Game Preview"
#define GAME_WINDOW_DEFAULT_WIDTH 1333
#define GAME_WINDOW_DEFAULT_HEIGHT 768

#define GAME_WINDOW_DEFAULT_POS_X 588
#define GAME_WINDOW_DEFAULT_POS_Y 30


//////////////////////////////////////////
// Input settings
//////////////////////////////////////////
#define NUM_KEYBOARD_KEYS 1024
#define NUM_MOUSE_KEYS 64

//! Printable keys
#define INPUT_KEY_SPACE              32
#define INPUT_KEY_APOSTROPHE         39  /* ' */
#define INPUT_KEY_COMMA              44  /* , */
#define INPUT_KEY_MINUS              45  /* - */
#define INPUT_KEY_PERIOD             46  /* . */
#define INPUT_KEY_SLASH              47  /* / */
#define INPUT_KEY_0                  48
#define INPUT_KEY_1                  49
#define INPUT_KEY_2                  50
#define INPUT_KEY_3                  51
#define INPUT_KEY_4                  52
#define INPUT_KEY_5                  53
#define INPUT_KEY_6                  54
#define INPUT_KEY_7                  55
#define INPUT_KEY_8                  56
#define INPUT_KEY_9                  57
#define INPUT_KEY_SEMICOLON          59  /* ; */
#define INPUT_KEY_EQUAL              61  /* = */
#define INPUT_KEY_A                  65
#define INPUT_KEY_B                  66
#define INPUT_KEY_C                  67
#define INPUT_KEY_D                  68
#define INPUT_KEY_E                  69
#define INPUT_KEY_F                  70
#define INPUT_KEY_G                  71
#define INPUT_KEY_H                  72
#define INPUT_KEY_I                  73
#define INPUT_KEY_J                  74
#define INPUT_KEY_K                  75
#define INPUT_KEY_L                  76
#define INPUT_KEY_M                  77
#define INPUT_KEY_N                  78
#define INPUT_KEY_O                  79
#define INPUT_KEY_P                  80
#define INPUT_KEY_Q                  81
#define INPUT_KEY_R                  82
#define INPUT_KEY_S                  83
#define INPUT_KEY_T                  84
#define INPUT_KEY_U                  85
#define INPUT_KEY_V                  86
#define INPUT_KEY_W                  87
#define INPUT_KEY_X                  88
#define INPUT_KEY_Y                  89
#define INPUT_KEY_Z                  90
#define INPUT_KEY_LEFT_BRACKET       91  /* [ */
#define INPUT_KEY_BACKSLASH          92  /* \ */
#define INPUT_KEY_RIGHT_BRACKET      93  /* ] */
#define INPUT_KEY_GRAVE_ACCENT       96  /* ` */
#define INPUT_KEY_WORLD_1            161 /* non-US #1 */
#define INPUT_KEY_WORLD_2            162 /* non-US #2 */

//! Function keys
#define INPUT_KEY_ESCAPE             256
#define INPUT_KEY_ENTER              257
#define INPUT_KEY_TAB                258
#define INPUT_KEY_BACKSPACE          259
#define INPUT_KEY_INSERT             260
#define INPUT_KEY_DELETE             261
#define INPUT_KEY_RIGHT              262
#define INPUT_KEY_LEFT               263
#define INPUT_KEY_DOWN               264
#define INPUT_KEY_UP                 265
#define INPUT_KEY_PAGE_UP            266
#define INPUT_KEY_PAGE_DOWN          267
#define INPUT_KEY_HOME               268
#define INPUT_KEY_END                269
#define INPUT_KEY_CAPS_LOCK          280
#define INPUT_KEY_SCROLL_LOCK        281
#define INPUT_KEY_NUM_LOCK           282
#define INPUT_KEY_PRINT_SCREEN       283
#define INPUT_KEY_PAUSE              284
#define INPUT_KEY_F1                 290
#define INPUT_KEY_F2                 291
#define INPUT_KEY_F3                 292
#define INPUT_KEY_F4                 293
#define INPUT_KEY_F5                 294
#define INPUT_KEY_F6                 295
#define INPUT_KEY_F7                 296
#define INPUT_KEY_F8                 297
#define INPUT_KEY_F9                 298
#define INPUT_KEY_F10                299
#define INPUT_KEY_F11                300
#define INPUT_KEY_F12                301
#define INPUT_KEY_F13                302
#define INPUT_KEY_F14                303
#define INPUT_KEY_F15                304
#define INPUT_KEY_F16                305
#define INPUT_KEY_F17                306
#define INPUT_KEY_F18                307
#define INPUT_KEY_F19                308
#define INPUT_KEY_F20                309
#define INPUT_KEY_F21                310
#define INPUT_KEY_F22                311
#define INPUT_KEY_F23                312
#define INPUT_KEY_F24                313
#define INPUT_KEY_F25                314
#define INPUT_KEY_KP_0               320
#define INPUT_KEY_KP_1               321
#define INPUT_KEY_KP_2               322
#define INPUT_KEY_KP_3               323
#define INPUT_KEY_KP_4               324
#define INPUT_KEY_KP_5               325
#define INPUT_KEY_KP_6               326
#define INPUT_KEY_KP_7               327
#define INPUT_KEY_KP_8               328
#define INPUT_KEY_KP_9               329
#define INPUT_KEY_KP_DECIMAL         330
#define INPUT_KEY_KP_DIVIDE          331
#define INPUT_KEY_KP_MULTIPLY        332
#define INPUT_KEY_KP_SUBTRACT        333
#define INPUT_KEY_KP_ADD             334
#define INPUT_KEY_KP_ENTER           335
#define INPUT_KEY_KP_EQUAL           336
#define INPUT_KEY_LEFT_SHIFT         340
#define INPUT_KEY_LEFT_CONTROL       341
#define INPUT_KEY_LEFT_ALT           342
#define INPUT_KEY_LEFT_SUPER         343
#define INPUT_KEY_RIGHT_SHIFT        344
#define INPUT_KEY_RIGHT_CONTROL      345
#define INPUT_KEY_RIGHT_ALT          346
#define INPUT_KEY_RIGHT_SUPER        347
#define INPUT_KEY_MENU               348

//! Mouse keys
#define INPUT_MOUSE_BUTTON_1         0
#define INPUT_MOUSE_BUTTON_2         1
#define INPUT_MOUSE_BUTTON_3         2
#define INPUT_MOUSE_BUTTON_4         3
#define INPUT_MOUSE_BUTTON_5         4
#define INPUT_MOUSE_BUTTON_6         5
#define INPUT_MOUSE_BUTTON_7         6
#define INPUT_MOUSE_BUTTON_8         7
#define INPUT_MOUSE_BUTTON_LAST      INPUT_MOUSE_BUTTON_8
#define INPUT_MOUSE_BUTTON_LEFT      INPUT_MOUSE_BUTTON_1
#define INPUT_MOUSE_BUTTON_RIGHT     INPUT_MOUSE_BUTTON_2
#define INPUT_MOUSE_BUTTON_MIDDLE    INPUT_MOUSE_BUTTON_3


//////////////////////////////////////////
// Weird stuff
//////////////////////////////////////////

//! Magic number used as identificator root module Engine
#define MAGIC_BASE_MODULE_NUMBER 42