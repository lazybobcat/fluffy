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
        include/fluffy/game/camera_controller.hpp src/game/camera_controller.cpp
        include/fluffy/resources/resource.hpp src/resources/resource.cpp
        include/fluffy/resources/resource_holder.hpp
        include/fluffy/api/modules.hpp src/api/modules.cpp
        include/fluffy/api/context.hpp src/api/context.cpp
        include/fluffy/graphics/renderer.hpp src/graphics/renderer.cpp
        include/fluffy/graphics/renderer_api.hpp
        include/fluffy/graphics/render_command.hpp
        include/fluffy/graphics/window.hpp
        include/fluffy/graphics/color.hpp src/graphics/color.cpp
        include/fluffy/graphics/shader.hpp
        include/fluffy/graphics/texture.hpp
        include/fluffy/graphics/vertex.hpp src/graphics/vertex.cpp
        include/fluffy/graphics/transform.hpp src/graphics/transform.cpp
        include/fluffy/graphics/transformable.hpp src/graphics/transformable.cpp
        include/fluffy/graphics/camera.hpp src/graphics/camera.cpp
        include/fluffy/input/mouse.hpp
        include/fluffy/input/keyboard.hpp
        include/fluffy/input/input.hpp src/input/input.cpp
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
target_link_libraries(fluffy-core fluffy-utils)