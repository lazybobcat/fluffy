//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 27/12/15.
//

#pragma once

#include <string>

// General configurations
#define FLUFFY_LOG_FILE "logs.html"

// Debug configurations
#define FLUFFY_ENV_TEST test
#define FLUFFY_ENV_DEBUG debug
#define FLUFFY_ENV_RELEASE release

// Json
#if FLUFFY_ENV == FLUFFY_ENV_TEST
    #define FLUFFY_DEBUG_COMPACT_JSON true
#else
    #define FLUFFY_DEBUG_COMPACT_JSON false
#endif

// ECS configurations
#define FLUFFY_ECS_MAX_COMPONENTS 128;
