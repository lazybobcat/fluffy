cmake_minimum_required(VERSION 3.3)
project(fluffy)
#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/selene/include ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/jsoncpp ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/bandit)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fPIC")

set(SOURCE_FILES extlibs/jsoncpp/jsoncpp.cpp src/Fluffy/Utility/String.cpp src/Fluffy/ECS/Entity.cpp src/Fluffy/Utility/Debuggable.cpp src/Fluffy/Utility/Logger.cpp src/Fluffy/ECS/EntityManager.cpp include/Fluffy/ECS/Entity.inl include/Fluffy/ECS/ComponentHandle.inl src/Fluffy/ECS/Exception/ComponentNotFoundException.cpp include/Fluffy/ECS/Exception/EntityNotFoundException.hpp include/Fluffy/ECS/View/EntityComponentView.hpp src/Fluffy/ECS/Exception/EntityNotFoundException.cpp include/Fluffy/ECS/EntityManager.inl include/Fluffy/ECS/View/EntityComponentView.inl)
set(TEST_SOURCE_FILES src/Fluffy/Test/tests.cpp src/Fluffy/Test/Utility/StringTest.cpp)

# Building libfluffy
add_library(fluffy SHARED ${SOURCE_FILES})
install(TARGETS fluffy DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)
target_link_libraries(fluffy sfml-system sfml-window sfml-graphics sfml-audio sfml-network ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/lua/liblua.a dl)

# Building unittests
add_executable(unittests ${SOURCE_FILES} ${TEST_SOURCE_FILES})
target_link_libraries(unittests ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/lua/liblua.a dl)
