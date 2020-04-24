configure_file(include/fluffy/definitions.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/include/fluffy/definitions.hpp @ONLY)

set(SOURCE_FILES
        include/fluffy/pch.hpp src/pch.cpp
        include/fluffy/definitions.hpp
        include/fluffy/assert.hpp
        include/fluffy/event/event.hpp src/event/event.cpp
        include/fluffy/event/event_manager.hpp src/event/event_manager.cpp
        include/fluffy/state/state.hpp src/state/state.cpp
        include/fluffy/state/state_stack.hpp src/state/state_stack.cpp
        include/fluffy/game/game.hpp src/game/game.cpp
        include/fluffy/game/game_loader.hpp src/game/game_loader.cpp
        include/fluffy/game/game_main.hpp include/fluffy/game/game_main.inl src/game/game_main.cpp
        include/fluffy/game/game_loop.hpp src/game/game_loop.cpp
        include/fluffy/resources/resource.hpp src/resources/resource.cpp
        include/fluffy/resources/resource_holder.hpp
        include/fluffy/api/modules.hpp src/api/modules.cpp
        include/fluffy/api/context.hpp src/api/context.cpp
        include/fluffy/graphics/renderer.hpp src/graphics/renderer.cpp
        include/fluffy/graphics/window.hpp
        include/fluffy/graphics/platform/glfw_window.hpp src/graphics/platform/glfw_window.cpp
        include/fluffy/graphics/platform/opengl.hpp src/graphics/glad.c
        include/fluffy/graphics/color.hpp src/graphics/color.cpp
        include/fluffy/graphics/vertex.hpp
        include/fluffy/graphics/shader.hpp src/graphics/shader.cpp
        include/fluffy/graphics/texture.hpp src/graphics/texture.cpp
        include/fluffy/graphics/platform/opengl_shader.hpp src/graphics/platform/opengl_shader.cpp
        include/fluffy/graphics/platform/opengl_texture.hpp src/graphics/platform/opengl_texture.cpp
        src/graphics/vertex.cpp include/fluffy/graphics/vertex_array.hpp src/graphics/vertex_array.cpp
        include/fluffy/graphics/transform.hpp src/graphics/transform.cpp
        include/fluffy/graphics/transformable.hpp
        include/fluffy/fluffy_core.hpp src/graphics/window.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(fluffy-core ${SOURCE_FILES})
add_precompiled_header(fluffy-core include/fluffy/pch.hpp FORCEINCLUDE)
target_include_directories(fluffy-core PUBLIC "include")
target_link_libraries(fluffy-core fluffy-utils)