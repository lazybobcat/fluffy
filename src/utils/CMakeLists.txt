set(SOURCE_FILES
        contrib/jsoncpp/jsoncpp.cpp
        include/fluffy/definitions.hpp
        include/fluffy/time/clock.hpp src/time/clock.cpp
        include/fluffy/serialization/serializable.hpp
        include/fluffy/serialization/json_serializer.hpp src/serialization/json_serializer.cpp
        include/fluffy/utils/logger.hpp src/utils/logger.cpp
        include/fluffy/utils/pool.hpp src/utils/pool.cpp
        include/fluffy/math/random.hpp src/math/random.cpp
        include/fluffy/service/service_container.hpp src/service/service_container.cpp
        include/fluffy/text/string.hpp src/text/string.cpp
        include/fluffy/time/time.hpp src/time/time.cpp
        include/fluffy/signal/slot.hpp src/signal/slot.cpp
        include/fluffy/signal/signal.hpp src/signal/signal.cpp
        include/fluffy/fluffy_utils.hpp)

add_library(fluffy-utils ${SOURCE_FILES})
target_include_directories(fluffy-utils PUBLIC "include" "contrib/jsoncpp")