cmake_minimum_required(VERSION 3.3)
project(fluffy)
#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/extlibs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES "src/Fluffy/*.cpp")

add_library(fluffy SHARED ${SOURCE_FILES})
install(TARGETS fluffy DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)