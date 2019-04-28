set(SOURCE_FILES
        tests.cpp
        utils/string_test.cpp
        utils/serialization_test.cpp
        utils/random_test.cpp
        core/scene_test.cpp
        core/state_test.cpp
        ecs/ecs_test.cpp)

add_executable(unittests ${SOURCE_FILES})
target_link_libraries(unittests ${FLUFFY_EXTERNAL_LIBS} ${FLUFFY_INTERNAL_LIBS})