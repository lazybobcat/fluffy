configure_file(include/fluffy/definitions.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/include/fluffy/definitions.hpp @ONLY)

set(SOURCE_FILES
        include/fluffy/pch.hpp src/pch.cpp
        include/fluffy/definitions.hpp
        include/fluffy/assert.hpp
        include/fluffy/event/event.hpp src/event/event.cpp
        include/fluffy/event/event_manager.hpp src/event/event_manager.cpp
        include/fluffy/layer/layer.hpp src/layer/layer.cpp
        include/fluffy/layer/layer_stack.hpp src/layer/layer_stack.cpp
        include/fluffy/game/game.hpp src/game/game.cpp
        include/fluffy/game/game_loader.hpp src/game/game_loader.cpp
        include/fluffy/game/game_main.hpp include/fluffy/game/game_main.inl src/game/game_main.cpp
        include/fluffy/game/game_loop.hpp src/game/game_loop.cpp
        include/fluffy/game/camera_controller.hpp src/game/camera_controller.cpp
        include/fluffy/resources/resource_library.hpp src/resources/resource_library.cpp
        include/fluffy/resources/resource_metadata.hpp src/resources/resource_metadata.cpp
        include/fluffy/resources/resource_collection.hpp src/resources/resource_collection.cpp
        include/fluffy/resources/resource_loader.hpp src/resources/resource_loader.cpp
        include/fluffy/resources/resource.hpp src/resources/resource.cpp
        include/fluffy/api/modules.hpp src/api/modules.cpp
        include/fluffy/api/context.hpp src/api/context.cpp
        include/fluffy/graphics/vertex.hpp src/graphics/vertex.cpp
        include/fluffy/graphics/window.hpp
        include/fluffy/graphics/render_target.hpp src/graphics/render_target.cpp
        include/fluffy/graphics/render_context.hpp src/graphics/render_context.cpp
        include/fluffy/graphics/render_states.hpp
        include/fluffy/graphics/painter.hpp src/graphics/painter.cpp
        include/fluffy/graphics/color.hpp src/graphics/color.cpp
        include/fluffy/graphics/shader.hpp
        include/fluffy/graphics/texture.hpp
        include/fluffy/graphics/vertex_buffers.hpp src/graphics/vertex_buffers.cpp
        include/fluffy/graphics/transformable.hpp src/graphics/transformable.cpp
        include/fluffy/graphics/camera.hpp src/graphics/camera.cpp
        include/fluffy/graphics/drawable.hpp
        include/fluffy/graphics/shape.hpp src/graphics/shape.cpp
        include/fluffy/graphics/rectangle_shape.hpp src/graphics/rectangle_shape.cpp
        include/fluffy/input/mouse.hpp
        include/fluffy/input/keyboard.hpp
        include/fluffy/input/input.hpp src/input/input.cpp
        include/fluffy/profiling/profiler.hpp src/profiling/profiler.cpp
        include/fluffy/profiling/scope_profiling.hpp src/profiling/scope_profiling.cpp
        include/fluffy/profiling/memory_profiling.hpp src/profiling/memory_profiling.cpp
        include/fluffy/profiling/rendering_profiling.hpp src/profiling/rendering_profiling.cpp
        include/fluffy/imgui/imgui_element.hpp src/imgui/imgui_element.cpp
        include/fluffy/imgui/imgui_container.hpp src/imgui/imgui_container.cpp
        include/fluffy/imgui/imgui_window.hpp src/imgui/imgui_window.cpp
        include/fluffy/fluffy_core.hpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(fluffy-core ${SOURCE_FILES})
if(WIN32)
    # Need to fix an issue with this @todo
    #add_precompiled_header(fluffy-core fluffy/pch.hpp FORCEINCLUDE SOURCE_CXX src/pch.cpp)
elseif(UNIX)
    add_precompiled_header(fluffy-core include/fluffy/pch.hpp FORCEINCLUDE)
endif()
target_include_directories(fluffy-core PUBLIC "include")
target_link_libraries(fluffy-core fluffy-utils imgui-flame-graph)