

# Create global project name variable
set(PROJECT_NAME SYEngine)
set(MAIN_EXE_NAME SYEngine)

# Set project name
project(${PROJECT_NAME})
cmake_minimum_required(VERSION 3.8)

# Use solution folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "BUILD ACTIONS")

# Set C++17
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else()
  set(CMAKE_CXX_STANDARD 17)
endif(MSVC) 


# Set version
set(CMAKE_PROJECT_VERSION_MAJOR 0)
set(CMAKE_PROJECT_VERSION_MINOR 0)
set(CMAKE_PROJECT_VERSION_PATCH 1)
set(CMAKE_PROJECT_VERSION ${CMAKE_PROJECT_VERSION_MAJOR}.${CMAKE_PROJECT_VERSION_MINOR}.${CMAKE_PROJECT_VERSION_PATCH})

# Set the correct macro directory path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")


# Define public options
option(DEBUG "Debug mode (strict compile, all warnings)" OFF)


# Print CLI helper message
message("")
message(
  "THIS IS HOW TO USE OPTIONS"
)
message("")


# Report where engine will be installed
message(STATUS "Install engine to: ${CMAKE_INSTALL_PREFIX}")
    

# Add project
add_subdirectory(SYEngine)