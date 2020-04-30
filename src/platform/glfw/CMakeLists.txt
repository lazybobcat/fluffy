set(SOURCE_FILES
        src/glfw.hpp
        src/glfw_functions.hpp src/glfw_functions.cpp
        src/glfw_window.hpp src/glfw_window.cpp
        src/glfw_input_impl.cpp
        src/imgui_impl_glfw.h src/imgui_impl_glfw.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(fluffy-glfw ${SOURCE_FILES})
target_link_libraries(fluffy-glfw fluffy-core fluffy-utils)