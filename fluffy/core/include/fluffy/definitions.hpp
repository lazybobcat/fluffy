#pragma once

#include <memory>
#include <string>

// General configurations
#define FLUFFY_VERSION "0.1.0"
#define FLUFFY_LOG_FILE "logs.txt"
#define FLUFFY_PROFILE_FILE "scope_profile.json"
#define FLUFFY_DEBUG_COMPACT_JSON true

#ifdef FLUFFY_DEBUG
#define FLUFFY_PROFILING_ACTIVE
#endif

// OpenGL configurations
#define OPENGL_MAJOR_VERSION 4
#define OPENGL_MINOR_VERSION 5

namespace Fluffy {
template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T, typename... Args>
constexpr Ref<T> CreateRef(Args&&... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

template<typename T>
using WeakRef = std::weak_ptr<T>;

template<typename T>
using Unique = std::unique_ptr<T>;
template<typename T, typename... Args>
constexpr Unique<T> CreateUnique(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

using Char32   = std::uint32_t;
using String   = std::string;
using String32 = std::u32string;
}
