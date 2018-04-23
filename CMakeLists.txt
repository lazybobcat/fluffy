cmake_minimum_required(VERSION 3.3)
project(fluffy)
#set(CMAKE_BUILD_TYPE Release)
#set(FLUFFY_ENV release)
set(CMAKE_BUILD_TYPE Debug)
set(FLUFFY_ENV debug)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/ChaiScript/include ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/jsoncpp ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/bandit)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fPIC")

set(SOURCE_FILES include/Fluffy/definitions.hpp extlibs/jsoncpp/jsoncpp.cpp include/Fluffy/Utility/Pool.inl src/Fluffy/Utility/Pool.cpp src/Fluffy/Utility/String.cpp src/Fluffy/ECS/Entity.cpp src/Fluffy/Utility/Logger.cpp src/Fluffy/ECS/EntityManager.cpp include/Fluffy/ECS/Entity.inl include/Fluffy/ECS/ComponentHandle.inl src/Fluffy/ECS/Exception/ComponentNotFoundException.cpp src/Fluffy/ECS/Exception/EntityNotFoundException.cpp include/Fluffy/ECS/EntityManager.inl include/Fluffy/ECS/View/EntityComponentView.inl src/Fluffy/ECS/Component.cpp src/Fluffy/ECS/Exception/BadComponentDestruction.cpp src/Fluffy/ECS/System.cpp src/Fluffy/Event/Slot.cpp src/Fluffy/Event/Signal.cpp include/Fluffy/Event/Signal.inl src/Fluffy/Event/Event.cpp src/Fluffy/Event/EventManager.cpp include/Fluffy/Event/EventManager.inl src/Fluffy/ECS/SystemManager.cpp include/Fluffy/ECS/SystemManager.hpp include/Fluffy/ECS/SystemManager.inl src/Fluffy/Utility/Clock.cpp src/Fluffy/Utility/Time.cpp include/Fluffy/Utility/Random.hpp src/Fluffy/Utility/Random.cpp src/Fluffy/State/State.cpp src/Fluffy/State/StateStack.cpp include/Fluffy/State/StateStack.inl include/Fluffy/State/State.inl include/Fluffy/Utility/ServiceContainer.inl src/Fluffy/Utility/ServiceContainer.cpp include/Fluffy/Scene/SceneNode.hpp src/Fluffy/Scene/SceneNode.cpp include/Fluffy/Scene/Scene.hpp src/Fluffy/Scene/Scene.cpp include/Fluffy/Utility/Serializable.hpp include/Fluffy/Utility/JsonSerializer.hpp src/Fluffy/Utility/JsonSerializer.cpp include/Fluffy/Asset/AssetHolder.hpp include/Fluffy/Asset/AssetHolder.inl include/Fluffy/Asset/MusicPlayer.hpp src/Fluffy/Asset/MusicPlayer.cpp include/Fluffy/Asset/MusicPlayer.inl include/Fluffy/Asset/SoundPlayer.hpp include/Fluffy/Asset/SoundPlayer.inl src/Fluffy/Asset/SoundPlayer.cpp)
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
