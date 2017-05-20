cmake_minimum_required(VERSION 3.3)
project(fluffy)
#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/selene/include ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/jsoncpp ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/bandit)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")

set(SOURCE_FILES extlibs/jsoncpp/jsoncpp.cpp src/Fluffy/Utility/String.cpp src/Fluffy/ECS/Entity.cpp src/Fluffy/Utility/Debuggable.cpp src/Fluffy/Utility/Logger.cpp src/Fluffy/ECS/EntityManager.cpp include/Fluffy/ECS/Entity.inl include/Fluffy/ECS/ComponentHandle.inl src/Fluffy/ECS/Exception/ComponentNotFoundException.cpp)
set(TEST_SOURCE_FILES src/Fluffy/Test/tests.cpp)

add_library(fluffy SHARED ${SOURCE_FILES})
install(TARGETS fluffy DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)
add_executable(unittest ${TEST_SOURCE_FILES})
target_link_libraries(fluffy sfml-system sfml-window sfml-graphics sfml-audio sfml-network ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/lua/liblua.a dl)
