set(SOURCE_FILES
        src/glad.c
        src/opengl.hpp src/opengl.cpp
        src/opengl_shader.hpp src/opengl_shader.cpp
        src/opengl_texture.hpp src/opengl_texture.cpp
        src/opengl_vertex.hpp src/opengl_vertex.cpp
        src/imgui_impl_opengl3.h src/imgui_impl_opengl3.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(fluffy-opengl ${SOURCE_FILES})
target_link_libraries(fluffy-opengl fluffy-core fluffy-utils)
target_include_directories(fluffy-opengl PUBLIC "src")