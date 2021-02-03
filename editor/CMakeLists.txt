set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/build)

set(SOURCE_FILES
        editor.cpp
        ui/panels/log_window.cpp
        ui/panels/profiling_window.cpp
        ui/panels/toolbar.cpp
        ui/panels/viewport_window.cpp
        ui/panels/scene_hierarchy_panel.cpp
        ui/panels/inspector_panel.cpp
        ui/layout.hpp
        registry/plugin_registry.cpp
        registry/component_registry.cpp
        plugins/fluffy_plugin.cpp
        modules/fluffy_editor_module.cpp
        ui/panels/add_component_window.cpp
        layers/editor_state.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(editor ${SOURCE_FILES})
target_link_libraries(editor ${FLUFFY_INTERNAL_LIBS} ${FLUFFY_EXTERNAL_LIBS})