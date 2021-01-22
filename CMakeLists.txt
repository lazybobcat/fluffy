cmake_minimum_required(VERSION 3.8.2)
project(fluffy VERSION 0.1.0)

if(WIN32)
    message("Making for windows environment...")
    set(FLUFFY_EXTERNAL_LIBS opengl32 glfw)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std:c++latest")
elseif(UNIX)
    message("Making for unix environment...")
    set(FLUFFY_EXTERNAL_LIBS pthread GL glfw X11 Xrandr Xi)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC")
else()
    message(FATAL_ERROR "Your platform is not supported! (yet?)")
endif()

set(FLUFFY_INTERNAL_LIBS fmt imgui fluffy-utils fluffy-core fluffy-ecs)

# Platform dependencies
set(FLUFFY_USE_OPENGL 1)
set(FLUFFY_USE_OPENGL_ES2 0)
set(FLUFFY_USE_OPENGL_ES3 0)
set(FLUFFY_USE_GLFW 1)

# CMake configurations
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/build)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/build)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -DFLUFFY_DEBUG")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Plugins
include(cmake/PrecompiledHeader.cmake) # If CMake < 3.16, precompiled headers are not supported out of the box

# Debug libs
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/contrib/debug)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/contrib/glfw)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/contrib/glfw/include)

# FMT
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/contrib/fmt)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/contrib/fmt/include)

# ImGUI
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/contrib/imgui)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/contrib/imgui)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/contrib/imgui-flame-graph)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/contrib/imgui-flame-graph)

# Contrib libraries
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/contrib/glad/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/contrib/glm)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/contrib/stb)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/contrib/circular_buffer)

# Fluffy
add_subdirectory(src/utils)
add_subdirectory(src/ecs)
add_subdirectory(src/core)
add_subdirectory(src/platform)

# Building libfluffy
add_library(fluffy SHARED ${CMAKE_CURRENT_SOURCE_DIR}/include/fluffy.hpp)
target_link_libraries(fluffy ${FLUFFY_INTERNAL_LIBS} ${FLUFFY_EXTERNAL_LIBS})

# Tests
add_subdirectory(tests)

# Sandbox
add_subdirectory(sandbox)
