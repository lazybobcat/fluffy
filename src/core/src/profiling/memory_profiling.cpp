#include <fluffy/profiling/memory_profiling.hpp>

using namespace Fluffy;

#ifdef FLUFFY_PROFILING_ACTIVE

void* operator new(std::size_t size)
{
    void* p = malloc(size);
    if (!p)
        throw std::bad_alloc();

    memory_usage += size;

    return p;
}

void* operator new[](std::size_t size)
{
    void* p = malloc(size);
    if (!p)
        throw std::bad_alloc();

    memory_usage += size;

    return p;
}

void* operator new[](std::size_t size, const std::nothrow_t&) noexcept
{
    void* p = malloc(size);

    memory_usage += size;

    return p;
}
void* operator new(std::size_t size, const std::nothrow_t&) noexcept
{
    void* p = malloc(size);

    memory_usage += size;

    return p;
}

void operator delete(void* ptr, std::size_t size) noexcept
{
    free(ptr);

    if (nullptr != ptr) {
        memory_usage -= size;
    }
}

void operator delete[](void* ptr, std::size_t size) noexcept
{
    free(ptr);

    if (nullptr != ptr) {
        memory_usage -= size;
    }
}

#endif