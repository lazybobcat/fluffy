set(SOURCE_FILES
        include/fluffy/event/event.hpp src/event/event.cpp
        include/fluffy/event/event_manager.hpp src/event/event_manager.cpp
        include/fluffy/scene/scene_node.hpp src/scene/scene_node.cpp
        include/fluffy/scene/scene.hpp src/scene/scene.cpp
        include/fluffy/state/state.hpp src/state/state.cpp include/fluffy/state/state.inl
        include/fluffy/state/state_stack.hpp src/state/state_stack.cpp
        include/fluffy/game/game.hpp src/game/game.cpp
        include/fluffy/game/game_loader.hpp
        include/fluffy/game/game_main.hpp include/fluffy/game/game_main.inl src/game/game_main.cpp
        include/fluffy/game/game_loop.hpp src/game/game_loop.cpp
        include/fluffy/fluffy_core.hpp src/game/game_loader.cpp)

add_library(fluffy-core ${SOURCE_FILES})
target_include_directories(fluffy-core PUBLIC "include")
target_link_libraries(fluffy-core fluffy-utils sfml-graphics)