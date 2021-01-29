set(SOURCE_FILES
        tests.cpp
        utils/serialization_test.cpp
        utils/random_test.cpp
        core/state_test.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/contrib/bandit)
add_executable(unittests ${SOURCE_FILES})
target_compile_definitions(unittests PUBLIC FLUFFY_UNIT_TESTING)
target_link_libraries(unittests ${FLUFFY_INTERNAL_LIBS} ${FLUFFY_EXTERNAL_LIBS})