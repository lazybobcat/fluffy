set(SOURCE_FILES
        src/glfw_window.hpp src/glfw_window.cpp
        src/glfw_input_impl.cpp src/glfw.hpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(fluffy-glfw ${SOURCE_FILES})
target_link_libraries(fluffy-glfw fluffy-core fluffy-utils)