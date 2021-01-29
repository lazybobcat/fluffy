set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/build)

set(SOURCE_FILES
        editor.cpp
        windows/log_window.cpp
        windows/profiling_window.cpp
        windows/toolbar_window.cpp
        windows/viewport_window.cpp
        windows/scene_hierarchy_window.cpp
        windows/inspector_window.cpp
        layers/editor_state.cpp)

add_executable(editor ${SOURCE_FILES})
target_link_libraries(editor ${FLUFFY_INTERNAL_LIBS} ${FLUFFY_EXTERNAL_LIBS})