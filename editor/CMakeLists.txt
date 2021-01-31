set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/build)

set(SOURCE_FILES
        editor.cpp
        ui/windows/log_window.cpp
        ui/windows/profiling_window.cpp
        ui/windows/toolbar_window.cpp
        ui/windows/viewport_window.cpp
        ui/windows/scene_hierarchy_window.cpp
        ui/windows/inspector_window.cpp
        layers/editor_state.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(editor ${SOURCE_FILES})
target_link_libraries(editor ${FLUFFY_INTERNAL_LIBS} ${FLUFFY_EXTERNAL_LIBS})