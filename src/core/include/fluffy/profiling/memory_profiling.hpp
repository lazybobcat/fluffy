#pragma once

#include <fluffy/definitions.hpp>

#ifdef FLUFFY_PROFILING_ACTIVE

namespace Fluffy {

inline std::uint64_t memory_usage;

}

void* operator new(std::size_t size);
void* operator new[](std::size_t size);
void* operator new[](std::size_t size, const std::nothrow_t&) noexcept;
void* operator new(std::size_t size, const std::nothrow_t&) noexcept;

void operator delete(void* ptr, std::size_t size) noexcept;
void operator delete[](void* ptr, std::size_t size) noexcept;

#endif