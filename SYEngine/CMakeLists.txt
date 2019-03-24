
# Set include directories for SYEngine

set(SYENGINE_INCLUDE_DIRS
  ./scripts
  ./Diagnostics
  ./Helper
  ./Engine/LogicManager
  ./Engine/Core
  ./Engine/Core/Common
  ./Engine/Core/Abstract
  ./Engine/InputManager
  ./Engine/SceneManager
  ./Engine/SceneManager/Scene
  ./Engine/SceneManager/EntityManager/ComponentManager
  ./Engine/SceneManager/EntityManager/ComponentManager/Component
  ./Engine/SceneManager/EntityManager/ComponentManager/Component/Animation
  ./Engine/SceneManager/EntityManager/ComponentManager/Component/Lighting
  ./Engine/SceneManager/EntityManager/ComponentManager/Component/Physics
  ./Engine/SceneManager/EntityManager/ComponentManager/Component/Physics/PhysicsBodies
  ./Engine/SceneManager/EntityManager/ComponentManager/Component/Physics/Colliders
  ./Engine/SceneManager/EntityManager/ComponentManager/Component/Rendering
  ./Engine/SceneManager/EntityManager/ComponentManager/Component/Rendering/Material
  ./Engine/SceneManager/EntityManager/ComponentManager/Component/Rendering/Mesh
  ./Engine/SceneManager/EntityManager/ComponentManager/Component/Rendering/Mesh/Primitives
  ./Engine/SceneManager/EntityManager/ComponentManager/Component/Logic
  ./Engine/SceneManager/EntityManager/ComponentManager/Component/AI
  ./Engine/SceneManager/EntityManager/ComponentManager/Component/Controller
  ./Engine/SceneManager/EntityManager/ComponentManager/Component/Sound
  ./Engine/SceneManager/EntityManager/ComponentManager/Component/Window
  ./Engine/SceneManager/EntityManager/ComponentManager/MaterialManager
  ./Engine/SceneManager/EntityManager/ComponentManager/ControllerManager
  ./Engine/SceneManager/EntityManager/ComponentManager/TextureManager
  ./Engine/SceneManager/EntityManager/ComponentManager/SkyboxManager
  ./Engine/SceneManager/EntityManager/ComponentManager/ModelManager
  ./Engine/SceneManager/EntityManager/ComponentManager/MeshManager/Primitives
  ./Engine/SceneManager/EntityManager/ComponentManager/MeshManager
  ./Engine/OutputManager/AudioManager/SoundManager
  ./Engine/OutputManager/AudioManager/MusicManager
  ./Engine/OutputManager/AudioManager
  ./Engine/OutputManager
  ./Engine/NetworkManager
  ./Engine/OutputManager/RenderingManager/AnimationManager
  ./Engine/OutputManager/RenderingManager/SkyboxManager
  ./Engine/OutputManager/RenderingManager/WindowManager
  ./Engine/OutputManager/RenderingManager/ShadowManager/Shadow/
  ./Engine/OutputManager/RenderingManager/TextureManager
  ./Engine/OutputManager/RenderingManager/ModelManager
  ./Engine/OutputManager/RenderingManager/ShadowManager
  ./Engine/OutputManager/RenderingManager/ShaderManager/Shader
  ./Engine/OutputManager/RenderingManager/ShaderManager
  ./Engine/OutputManager/RenderingManager/MaterialManager
  ./Engine/OutputManager/RenderingManager/MeshManager/Primitives
  ./Engine/OutputManager/RenderingManager/UiManager/Ui
  ./Engine/OutputManager/RenderingManager/UiManager
  ./Engine/OutputManager/RenderingManager/MeshManager
  ./Engine/OutputManager/RenderingManager
  ./Engine/SimulationManager/PhysicsManager/bullet3parts
  ./Engine/SimulationManager/PhysicsManager
  ./Engine/LogicManager/ScriptManager
  ./Engine/LogicManager/AiManager
  ./Engine/SimulationManager
  ./Engine/SceneManager/EntityManager
  ./Engine/SceneManager/EntityManager/Entity
  ./Engine/SceneManager/EntityManager/Entity/WorldEntity/Camera
  ./Engine/SceneManager/EntityManager/Entity/WorldEntity/WorldObject/Primitive
  ./Engine/SceneManager/EntityManager/Entity/WorldEntity/WorldObject
  ./Engine/SceneManager/EntityManager/Entity/WorldEntity/Light
  ./Engine/SceneManager/EntityManager/Entity/WorldEntity
  ./Engine/SceneManager/EntityManager/Entity/ScreenEntity/UI
  ./Engine/SceneManager/EntityManager/Entity/ScreenEntity
  ./Engine/EngineAPI
  ./Engine
  ./Game/scripts/
)

# Get source files
file( 
  GLOB SYENGINE_SOURCE_MAIN
    "*.cpp"
)

file(
  GLOB_RECURSE SYENGINE_SOURCE_FILEPATHS
    "Diagnostics/*.h"
    "Diagnostics/*.cpp"
    "Engine/*.h"
    "Engine/*.cpp"
    "Game/*.h"
    "Game/*.cpp"
    "scripts/*.h"
    "scripts/*.cpp"
)



include_directories(${SYENGINE_INCLUDE_DIRS})

# Add files into structure from it's source file structure
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SYENGINE_SOURCE_FILEPATHS} ${SYENGINE_SOURCE_MAIN}) 

#############################
# Create engine executable
#############################
add_executable(
  ${MAIN_EXE_NAME} 
  ${SYENGINE_SOURCE_MAIN} ${SYENGINE_SOURCE_FILEPATHS}
)


# Add compiler definitions
target_compile_definitions(${MAIN_EXE_NAME} PRIVATE _DISABLE_EXTENDED_ALIGNED_STORAGE)
target_compile_definitions(${MAIN_EXE_NAME} PRIVATE -DGLEW_STATIC)
target_compile_definitions(${MAIN_EXE_NAME} PRIVATE GLM_FORCE_CXX17)

if(WIN32)
  add_compile_definitions(NOMINMAX)
else()
  
endif(WIN32)

# OpenGL is must have
find_package(OpenGL REQUIRED)
if (OpenGL_FOUND)
  # Add OpenGL include directories
  include_directories(${OPENGL_INCLUDE_DIRS})
  # Add OpenGL link libraries
  target_link_libraries(${MAIN_EXE_NAME} ${OPENGL_LIBRARIES})
endif()


# Add external dependencies
add_subdirectory(external)

#####################
# Bullet3
#####################
# Add include directories
target_include_directories(${MAIN_EXE_NAME} PUBLIC "${BULLET_2_83_INCLUDE_DIRS}")

# Link against it
target_link_libraries(${MAIN_EXE_NAME} ${BULLET_2_83_LIBS})

#####################
# GLFW
#####################
# Add include directories
target_include_directories(${MAIN_EXE_NAME} PUBLIC "${GLFW_3_0_INCLUDE_DIRS}")

# Link against it
target_link_libraries(${MAIN_EXE_NAME} ${GLFW_3_0_LIBS})


#####################
# GLEW
#####################
# Add include directories
target_include_directories(${MAIN_EXE_NAME} PUBLIC "${GLEW_2_1_0_INCLUDE_DIRS}")

# Link against it
target_link_libraries(${MAIN_EXE_NAME} ${GLEW_2_1_0_LIBS})


#####################
# Assimp
#####################
# Add include directories
target_include_directories(${MAIN_EXE_NAME} PUBLIC "${ASSIMP_4_1_0_INCLUDE_DIRS}")

# Link against it
target_link_libraries(${MAIN_EXE_NAME} ${ASSIMP_4_1_0_LIBS})


#####################
# ImGUI
#####################
file(
  GLOB_RECURSE IMGUI_SOURCES
  "external/imgui/imgui-1.66/src/*.cpp"
)
target_sources(${MAIN_EXE_NAME} PUBLIC ${IMGUI_SOURCES})

# Add include directories
target_include_directories(${MAIN_EXE_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/imgui-1.66/include")
target_include_directories(${MAIN_EXE_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/imgui-1.66/include/imgui")

#####################
# GLM
#####################
target_include_directories(${MAIN_EXE_NAME} PUBLIC "${GLM_0_9_9_0_INCLUDE_DIRS}")


#####################
# STB
#####################
# Add include directories
target_include_directories(${MAIN_EXE_NAME} PUBLIC "${STB_2_22_INCLUDE_DIRS}")
