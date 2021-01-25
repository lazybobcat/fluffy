set(SOURCE_FILES
        src/glad.c
        src/opengl.hpp
        src/opengl_shader.hpp src/opengl_shader.cpp
        src/opengl_texture.hpp src/opengl_texture.cpp
        src/opengl_vertex.hpp src/opengl_vertex.cpp
        src/imgui_impl_opengl3.h src/imgui_impl_opengl3.cpp
        src/opengl_render_target.hpp src/opengl_render_target.cpp
        src/opengl_video_module.hpp src/opengl_video_module.cpp
        src/opengl_painter.hpp src/opengl_painter.cpp
        src/glfw.hpp
        src/glfw_functions.hpp src/glfw_functions.cpp
        src/glfw_window.hpp src/glfw_window.cpp
        src/glfw_input_impl.cpp
        src/imgui_impl_glfw.h src/imgui_impl_glfw.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(fluffy-opengl ${SOURCE_FILES})
target_link_libraries(fluffy-opengl fluffy-core fluffy-utils)
target_include_directories(fluffy-opengl PUBLIC "src")