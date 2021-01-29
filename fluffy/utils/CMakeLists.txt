set(SOURCE_FILES
        ../contrib/jsoncpp/jsoncpp.cpp
        include/fluffy/time/clock.hpp src/time/clock.cpp
        include/fluffy/serialization/serializable.hpp
        include/fluffy/serialization/json_serializer.hpp src/serialization/json_serializer.cpp
        include/fluffy/utils/logger.hpp src/utils/logger.cpp
        include/fluffy/utils/pool.hpp src/utils/pool.cpp
        include/fluffy/math/random.hpp src/math/random.cpp
        include/fluffy/text/string.hpp src/text/string.cpp
        include/fluffy/time/time.hpp src/time/time.cpp
        include/fluffy/signal/slot.hpp src/signal/slot.cpp
        include/fluffy/signal/signal.hpp src/signal/signal.cpp
        include/fluffy/math/math.hpp
        include/fluffy/math/rectangle.hpp include/fluffy/math/rectangle.inl src/math/rectangle.cpp
        include/fluffy/file/path.hpp src/file/path.cpp
        include/fluffy/file/filesystem.hpp src/file/filesystem.cpp
        include/fluffy/fluffy_utils.hpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../core/include)

add_library(fluffy-utils ${SOURCE_FILES})
if(UNIX)
    target_link_libraries(fluffy-utils fmt stdc++fs)
else()
    target_link_libraries(fluffy-utils fmt)
endif()
target_include_directories(fluffy-utils PUBLIC "include" "../contrib/jsoncpp")