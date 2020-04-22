#pragma once

#include <fluffy/pch.hpp>
#include <fluffy/definitions.hpp>
#include <debugbreak.h>

#ifdef FLUFFY_DEBUG
#define FLUFFY_ASSERT(condition, message) FluffyAssert(condition, message, __FILE__, __LINE__)

inline void FluffyAssert(bool condition, const char* message, const char* file, int line)
{
    if (!condition) {
        FLUFFY_LOG_ERROR("Assert failed in " + Fluffy::toString(file) + " on line " + Fluffy::toString(line) + ": " + Fluffy::toString(message));
        debug_break();
    }
}
#else
#define FLUFFY_ASSERT(...)
#endif