#pragma once

#include <debugbreak.h>
#include <fluffy/definitions.hpp>
#include <fluffy/pch.hpp>

#ifdef FLUFFY_DEBUG
#define FLUFFY_ASSERT(condition, message) FluffyAssert(condition, message, __FILE__, __LINE__)

inline void FluffyAssert(bool condition, const char* message, const char* file, int line)
{
    if (!condition) {
        FLUFFY_LOG_ERROR("Assert failed in '{}' on line {}: {}", file, line, message);
        debug_break();
    }
}
#else
#define FLUFFY_ASSERT(...)
#endif