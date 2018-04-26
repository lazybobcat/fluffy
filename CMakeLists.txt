cmake_minimum_required(VERSION 3.8)
project(fluffy)
#set(FLUFFY_ENV release)
set(FLUFFY_ENV debug)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/ChaiScript/include ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/jsoncpp ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/bandit)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -fPIC")

set(SOURCE_FILES include/Fluffy/definitions.hpp
        extlibs/jsoncpp/jsoncpp.cpp
        include/Fluffy/Utility/NonCopyable.hpp
        include/Fluffy/Utility/Pool.hpp include/Fluffy/Utility/Pool.inl src/Fluffy/Utility/Pool.cpp
        include/Fluffy/Utility/String.hpp src/Fluffy/Utility/String.cpp
        include/Fluffy/Utility/Logger.hpp src/Fluffy/Utility/Logger.cpp
        include/Fluffy/ECS/EntityManager.hpp include/Fluffy/ECS/EntityManager.inl src/Fluffy/ECS/EntityManager.cpp
        include/Fluffy/ECS/Entity.hpp include/Fluffy/ECS/Entity.inl src/Fluffy/ECS/Entity.cpp
        include/Fluffy/ECS/ComponentHandle.hpp include/Fluffy/ECS/ComponentHandle.inl
        include/Fluffy/ECS/Exception/ComponentNotFoundException.hpp src/Fluffy/ECS/Exception/ComponentNotFoundException.cpp
        include/Fluffy/ECS/Exception/EntityNotFoundException.hpp src/Fluffy/ECS/Exception/EntityNotFoundException.cpp
        include/Fluffy/ECS/View/EntityComponentView.hpp include/Fluffy/ECS/View/EntityComponentView.inl
        include/Fluffy/ECS/Component.hpp src/Fluffy/ECS/Component.cpp
        include/Fluffy/ECS/Exception/BadComponentDestruction.hpp src/Fluffy/ECS/Exception/BadComponentDestruction.cpp
        include/Fluffy/ECS/System.hpp src/Fluffy/ECS/System.cpp
        include/Fluffy/Event/Slot.hpp src/Fluffy/Event/Slot.cpp
        include/Fluffy/Event/Signal.hpp include/Fluffy/Event/Signal.inl src/Fluffy/Event/Signal.cpp
        include/Fluffy/Event/Event.hpp src/Fluffy/Event/Event.cpp
        include/Fluffy/Event/EventManager.hpp include/Fluffy/Event/EventManager.inl src/Fluffy/Event/EventManager.cpp
        include/Fluffy/ECS/SystemManager.hpp include/Fluffy/ECS/SystemManager.inl src/Fluffy/ECS/SystemManager.cpp
        include/Fluffy/Utility/Clock.hpp src/Fluffy/Utility/Clock.cpp
        include/Fluffy/Utility/Time.hpp src/Fluffy/Utility/Time.cpp
        include/Fluffy/Utility/Random.hpp src/Fluffy/Utility/Random.cpp
        include/Fluffy/State/State.hpp src/Fluffy/State/State.cpp include/Fluffy/State/State.inl
        include/Fluffy/State/StateStack.hpp src/Fluffy/State/StateStack.cpp include/Fluffy/State/StateStack.inl
        include/Fluffy/Utility/ServiceContainer.hpp include/Fluffy/Utility/ServiceContainer.inl src/Fluffy/Utility/ServiceContainer.cpp
        include/Fluffy/Scene/SceneNode.hpp src/Fluffy/Scene/SceneNode.cpp
        include/Fluffy/Scene/Scene.hpp src/Fluffy/Scene/Scene.cpp
        include/Fluffy/Utility/Serializable.hpp
        include/Fluffy/Utility/JsonSerializer.hpp src/Fluffy/Utility/JsonSerializer.cpp
        include/Fluffy/Asset/AssetHolder.hpp include/Fluffy/Asset/AssetHolder.inl
        include/Fluffy/Asset/MusicPlayer.hpp include/Fluffy/Asset/MusicPlayer.inl src/Fluffy/Asset/MusicPlayer.cpp
        include/Fluffy/Asset/SoundPlayer.hpp include/Fluffy/Asset/SoundPlayer.inl src/Fluffy/Asset/SoundPlayer.cpp)
set(TEST_SOURCE_FILES tests/tests.cpp tests/Utility/StringTest.cpp tests/Utility/SerializationTest.cpp tests/Utility/SceneTest.cpp)

# Building libfluffy
add_library(fluffy SHARED ${SOURCE_FILES})
install(TARGETS fluffy DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)
target_compile_definitions(fluffy PRIVATE FLUFFY_ENV=${FLUFFY_ENV})
target_link_libraries(fluffy dl pthread sfml-system sfml-graphics)

# Building unittests
add_executable(unittests ${SOURCE_FILES} ${TEST_SOURCE_FILES})
target_compile_definitions(unittests PRIVATE FLUFFY_ENV=test)
target_link_libraries(unittests dl pthread sfml-system sfml-graphics)
