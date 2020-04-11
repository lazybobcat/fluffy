cmake_minimum_required(VERSION 3.8.2)
project(fluffy VERSION 0.1.0)

#set(CMAKE_BUILD_TYPE Release)
#set(FLUFFY_ENV release)
set(CMAKE_BUILD_TYPE Debug)
set(FLUFFY_ENV debug)

if (WIN32)
    set(FLUFFY_EXTERNAL_LIBS pthread opengl32 glfw)
elseif(UNIX)
    set(FLUFFY_EXTERNAL_LIBS pthread GL glfw X11 Xrandr Xi)
else()
    message(FATAL_ERROR "Your platform is not supported! (yet?)")
endif()
set(FLUFFY_INTERNAL_LIBS fluffy-utils fluffy-core fluffy-ecs)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/build)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/build)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Plugins
include(cmake/PrecompiledHeader.cmake) # If CMake < 3.16, precompiled headers are not supported out of the box

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/contrib/glfw)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/contrib/glfw/include)

# Glad
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/contrib/glad/include)

# GLM
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/contrib/glm)

# STB
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/contrib/stb)

# Fluffy
add_subdirectory(src)

# Building libfluffy
add_library(fluffy SHARED ${CMAKE_CURRENT_SOURCE_DIR}/include/fluffy.hpp)
target_link_libraries(fluffy ${FLUFFY_INTERNAL_LIBS} ${FLUFFY_EXTERNAL_LIBS})

# Tests
add_subdirectory(tests)
