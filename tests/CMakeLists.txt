set(SOURCE_FILES
        tests.cpp
        utils/string_test.cpp
        utils/serialization_test.cpp
        #utils/SceneTest.cpp
        #ecs/ECSTest.cpp
        utils/random_test.cpp
        )

add_executable(unittests ${SOURCE_FILES})
target_compile_definitions(unittests PRIVATE FLUFFY_ENV=test PRIVATE FLUFFY_VERSION=${PROJECT_VERSION})
target_link_libraries(unittests ${FLUFFY_EXTERNAL_LIBS} ${FLUFFY_INTERNAL_LIBS})