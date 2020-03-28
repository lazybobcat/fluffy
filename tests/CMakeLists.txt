set(SOURCE_FILES
        tests.cpp
        utils/string_test.cpp
        utils/serialization_test.cpp
        utils/random_test.cpp
        core/scene_test.cpp
        core/state_test.cpp
        ecs/ecs_test.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/contrib/bandit)
add_executable(unittests ${SOURCE_FILES})
target_link_libraries(unittests ${FLUFFY_INTERNAL_LIBS} ${FLUFFY_EXTERNAL_LIBS})

add_executable(gametest test_game.cpp)
target_link_libraries(gametest ${FLUFFY_INTERNAL_LIBS} ${FLUFFY_EXTERNAL_LIBS})