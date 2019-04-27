set(SOURCE_FILES
        contrib/jsoncpp/jsoncpp.cpp
        include/fluffy/definitions.hpp
        include/fluffy/clock.hpp src/clock.cpp
        include/fluffy/serializable.hpp
        include/fluffy/json_serializer.hpp src/json_serializer.cpp
        include/fluffy/logger.hpp src/logger.cpp
        include/fluffy/pool.hpp src/pool.cpp
        include/fluffy/random.hpp src/random.cpp
        include/fluffy/service_container.hpp src/service_container.cpp
        include/fluffy/string.hpp src/string.cpp
        include/fluffy/time.hpp src/time.cpp
        include/fluffy/fluffy_utils.hpp)

add_library(fluffy-utils ${SOURCE_FILES})
target_include_directories(fluffy-utils PUBLIC "include" "contrib/jsoncpp")