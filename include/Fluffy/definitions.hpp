//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 27/12/15.
//

#include <string>

#ifndef FLUFFY_DEFINITIONS_HPP
#define FLUFFY_DEFINITIONS_HPP

// General configurations
#ifndef FLUFFY_VERSION
    #define FLUFFY_MAJOR_VERSION "0"
    #define FLUFFY_MINOR_VERSION "01"
    #define FLUFFY_PATCH_VERSION "000"
    #define FLUFFY_VERSION FLUFFY_MAJOR_VERSION "." FLUFFY_MINOR_VERSION "." FLUFFY_PATCH_VERSION
#endif
#define FLUFFY_LOG_FILE "logs.html"

// Debug configurations
#define FLUFFY_ENV_TEST test
#define FLUFFY_ENV_RELEASE release
#ifndef FLUFFY_ENV
    #define FLUFFY_ENV FLUFFY_ENV_RELEASE
#endif

// Json
#if FLUFFY_ENV == FLUFFY_ENV_TEST
    #define FLUFFY_DEBUG_COMPACT_JSON true
#else
    #define FLUFFY_DEBUG_COMPACT_JSON false
#endif

// ECS configurations
#define FLUFFY_ECS_MAX_COMPONENTS 64;

#endif //FLUFFY_DEFINITIONS_HPP
