set(SOURCE_FILES
        include/fluffy/view/entity_component_view.hpp
        include/fluffy/component_handle.hpp
        include/fluffy/component.hpp src/component.cpp
        include/fluffy/entity.hpp src/entity.cpp
        include/fluffy/entity_manager.hpp src/entity_manager.cpp
        include/fluffy/system.hpp src/system.cpp
        include/fluffy/system_manager.hpp src/system_manager.cpp
        include/fluffy/fluffy_ecs.hpp)

add_library(fluffy-ecs ${SOURCE_FILES})
target_include_directories(fluffy-ecs PUBLIC "include")
target_link_libraries(fluffy-ecs fluffy-utils fluffy-core)