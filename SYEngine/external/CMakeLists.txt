
#####################
# Bullet3
#####################
## Version 2.83
set(BULLET_2_83_VERSION "2.83")
set(BULLET_2_83_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bullet3/bullet3-${BULLET_2_83_VERSION}/")
set(BULLET_2_83_INCLUDE_DIRS "${BULLET_2_83_DIR}include")
set(BULLET_2_83_LIBS BulletDynamics BulletCollision LinearMath Bullet3Common)

set(BULLET_2_83_VERSION "2.83" PARENT_SCOPE)
set(BULLET_2_83_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bullet3/bullet3-${BULLET_2_83_VERSION}/" PARENT_SCOPE)
set(BULLET_2_83_INCLUDE_DIRS "${BULLET_2_83_DIR}/src" PARENT_SCOPE)
set(BULLET_2_83_LIBS BulletDynamics BulletCollision LinearMath Bullet3Common PARENT_SCOPE)
#################

# Set options
set(USE_MSVC_RUNTIME_LIBRARY_DLL ON CACHE BOOL "" FORCE)
set(BUILD_BULLET2_DEMOS OFF CACHE BOOL "" FORCE)
set(BUILD_CLSOCKET OFF CACHE BOOL "" FORCE)
set(BUILD_CPU_DEMOS OFF CACHE BOOL "" FORCE)
set(BUILD_ENET OFF CACHE BOOL "" FORCE)
set(BUILD_EXTRAS OFF CACHE BOOL "" FORCE)
set(BUILD_OPENGL3_DEMOS OFF CACHE BOOL "" FORCE)
set(BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# Add it's repository
add_subdirectory(${BULLET_2_83_DIR})

# Organize into folders
set_target_properties(Bullet2FileLoader PROPERTIES FOLDER "external/Bullet3")
set_target_properties(Bullet3Collision PROPERTIES FOLDER "external/Bullet3")
set_target_properties(Bullet3Common PROPERTIES FOLDER "external/Bullet3")
set_target_properties(Bullet3Dynamics PROPERTIES FOLDER "external/Bullet3")
set_target_properties(Bullet3Geometry PROPERTIES FOLDER "external/Bullet3")
set_target_properties(Bullet3OpenCL_clew PROPERTIES FOLDER "external/Bullet3")
set_target_properties(BulletCollision PROPERTIES FOLDER "external/Bullet3")
set_target_properties(BulletDynamics PROPERTIES FOLDER "external/Bullet3")
set_target_properties(BulletInverseDynamics PROPERTIES FOLDER "external/Bullet3")
set_target_properties(BulletSoftBody PROPERTIES FOLDER "external/Bullet3")
set_target_properties(LinearMath PROPERTIES FOLDER "external/Bullet3")
set_target_properties(BulletInverseDynamics PROPERTIES FOLDER "external/Bullet3")


#####################
# GLFW
#####################
## Version 3.0
set(GLFW_3_0_VERSION "3.0")
set(GLFW_3_0_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glfw/glfw-${GLFW_3_0_VERSION}/")
set(GLFW_3_0_INCLUDE_DIRS "${GLFW_3_0_DIR}/include")
set(GLFW_3_0_LIBS glfw)

set(GLFW_3_0_VERSION "3.0" PARENT_SCOPE)
set(GLFW_3_0_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glfw/glfw-${GLFW_3_0_VERSION}/" PARENT_SCOPE)
set(GLFW_3_0_INCLUDE_DIRS "${GLFW_3_0_DIR}/include" PARENT_SCOPE)
set(GLFW_3_0_LIBS glfw PARENT_SCOPE)
#################

# Set options
set(GLFW_BUILD_EXAMPLES  OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS  OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS  OFF CACHE BOOL "" FORCE)

# Add it's repository
add_subdirectory(${GLFW_3_0_DIR})

# Organize into folders
set_target_properties(glfw PROPERTIES FOLDER "external/GLFW")
set_target_properties(uninstall PROPERTIES FOLDER "external/GLFW")   

#####################
# GLEW
#####################
## Version 2.1.0
set(GLEW_2_1_0_VERSION "2.1.0")
set(GLEW_2_1_0_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glew/glew-cmake-${GLEW_2_1_0_VERSION}/")
set(GLEW_2_1_0_INCLUDE_DIRS "${GLEW_2_1_0_DIR}include")
set(GLEW_2_1_0_LIBS libglew_static)

set(GLEW_2_1_0_VERSION "2.1.0" PARENT_SCOPE)
set(GLEW_2_1_0_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glew/glew-cmake-${GLEW_2_1_0_VERSION}/" PARENT_SCOPE)
set(GLEW_2_1_0_INCLUDE_DIRS "${GLEW_2_1_0_DIR}include" PARENT_SCOPE)
set(GLEW_2_1_0_LIBS libglew_static PARENT_SCOPE)
#####################


# Set options
set(glew-cmake_BUILD_SHARED  OFF CACHE BOOL "" FORCE)
set(glew-cmake_BUILD_STATIC  ON CACHE BOOL "" FORCE)
set(glew-cmake_BUILD_SINGLE_CONTEXT  ON CACHE BOOL "" FORCE)
set(glew-cmake_BUILD_MULTI_CONTEXT  OFF CACHE BOOL "" FORCE)

# Add it's repository
add_subdirectory(${GLEW_2_1_0_DIR})

# Organize into folders
set_target_properties(libglew_static PROPERTIES FOLDER "external/GLEW" )

#####################
# Assimp
#####################
## Version 4.1.0
set(ASSIMP_4_1_0_VERSION "4.1.0")
set(ASSIMP_4_1_0_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assimp/assimp-${ASSIMP_4_1_0_VERSION}/")
set(ASSIMP_4_1_0_INCLUDE_DIRS "${ASSIMP_4_1_0_DIR}/include") 
set(ASSIMP_4_1_0_LIBS assimp)

set(ASSIMP_4_1_0_VERSION "4.1.0" PARENT_SCOPE)
set(ASSIMP_4_1_0_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assimp/assimp-${ASSIMP_4_1_0_VERSION}/" PARENT_SCOPE)
set(ASSIMP_4_1_0_INCLUDE_DIRS "${ASSIMP_4_1_0_DIR}/include" PARENT_SCOPE) 
set(ASSIMP_4_1_0_LIBS assimp PARENT_SCOPE)
#####################

# Set options
set(ASSIMP_BUILD_TESTS  OFF CACHE BOOL "" FORCE)

# Add it's repository
add_subdirectory(${ASSIMP_4_1_0_DIR})

# Organize into folders
if (TARGET assimp)
	set_target_properties(assimp PROPERTIES FOLDER "external/Assimp")
endif()
if (TARGET assimp_cmd)
set_target_properties(assimp_cmd PROPERTIES FOLDER "external/Assimp")
endif()
if (TARGET zlib)
set_target_properties(zlib PROPERTIES FOLDER "external/Assimp")
endif()
if (TARGET zlibstatic)
set_target_properties(zlibstatic PROPERTIES FOLDER "external/Assimp")
endif()
if (TARGET IrrXML)
set_target_properties(IrrXML PROPERTIES FOLDER "external/Assimp")
endif()
if (TARGET UpdateAssimpLibsDebugSymbolsAndDLLs)
set_target_properties(UpdateAssimpLibsDebugSymbolsAndDLLs PROPERTIES FOLDER "external/Assimp")
endif()


#####################
# GLM
#####################
## Version 0.9.9.0
set(GLM_0_9_9_0_VERSION "0.9.9.0")
set(GLM_0_9_9_0_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glm/glm-${GLM_0_9_9_0_VERSION}/")
set(GLM_0_9_9_0_INCLUDE_DIRS "${GLM_0_9_9_0_DIR} ${GLM_0_9_9_0_DIR}/glm") 

set(GLM_0_9_9_0_VERSION "0.9.9.0" PARENT_SCOPE)
set(GLM_0_9_9_0_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glm/glm-${GLM_0_9_9_0_VERSION}/" PARENT_SCOPE)
set(GLM_0_9_9_0_INCLUDE_DIRS "${GLM_0_9_9_0_DIR}" "${GLM_0_9_9_0_DIR}/glm" PARENT_SCOPE) 
#####################


#####################
# STB
#####################
## Version 2.22 (STB Image)
set(STB_2_22_VERSION "2.22")
set(STB_2_22_DIR "${CMAKE_CURRENT_SOURCE_DIR}/stb/stb-${STB_2_22_VERSION}/")
set(STB_2_22_INCLUDE_DIRS "${STB_2_22_DIR}") 

set(STB_2_22_VERSION "2.22" PARENT_SCOPE)
set(STB_2_22_DIR "${CMAKE_CURRENT_SOURCE_DIR}/stb/stb-${STB_2_22_VERSION}/" PARENT_SCOPE)
set(STB_2_22_INCLUDE_DIRS "${STB_2_22_DIR}" PARENT_SCOPE)
#####################
