configure_file(include/fluffy/definitions.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/include/fluffy/definitions.hpp @ONLY)

set(SOURCE_FILES
        include/fluffy/pch.hpp src/pch.cpp
        include/fluffy/definitions.hpp
        include/fluffy/event/event.hpp src/event/event.cpp
        include/fluffy/event/event_manager.hpp src/event/event_manager.cpp
        include/fluffy/scene/scene_node.hpp src/scene/scene_node.cpp
        include/fluffy/scene/scene.hpp src/scene/scene.cpp
        include/fluffy/state/state.hpp src/state/state.cpp
        include/fluffy/state/state_stack.hpp src/state/state_stack.cpp
        include/fluffy/game/game.hpp src/game/game.cpp
        include/fluffy/game/game_loader.hpp src/game/game_loader.cpp
        include/fluffy/game/game_main.hpp include/fluffy/game/game_main.inl src/game/game_main.cpp
        include/fluffy/game/game_loop.hpp src/game/game_loop.cpp
        include/fluffy/resources/resource.hpp
        include/fluffy/resources/resource_holder.hpp
        include/fluffy/api/modules.hpp src/api/modules.cpp
        include/fluffy/api/context.hpp src/api/context.cpp
        include/fluffy/graphics/window.hpp
        include/fluffy/graphics/platform/glfw_window.hpp src/graphics/platform/glfw_window.cpp
        include/fluffy/graphics/platform/opengl.hpp src/graphics/glad.c
        include/fluffy/graphics/shader.hpp
        include/fluffy/graphics/platform/opengl_shader.hpp src/graphics/platform/opengl_shader.cpp
        include/fluffy/fluffy_core.hpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(fluffy-core ${SOURCE_FILES})
add_precompiled_header(fluffy-core include/fluffy/pch.hpp FORCEINCLUDE)
target_include_directories(fluffy-core PUBLIC "include")
target_link_libraries(fluffy-core fluffy-utils)