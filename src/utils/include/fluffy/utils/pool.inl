#include <fluffy/utils/pool.hpp>

using namespace Fluffy;

template<typename T>
std::size_t Pool<T>::size() const
{
    return mBlocks.size();
}

template<typename T>
void* Pool<T>::get(std::uint32_t n)
{
    FLUFFY_ASSERT(n < size(), "Request for undefined index in Pool");
    T object = mBlocks[n];

    return &mBlocks[n];
}

template<typename T>
void Pool<T>::set(std::uint32_t n, T&& object)
{
    FLUFFY_ASSERT(n < size(), "Request for undefined index in Pool");
    mBlocks[n] = std::move(object);
}

template<typename T>
void Pool<T>::expand(std::uint32_t n)
{
    mBlocks.resize(n);
}

template<typename T>
void Pool<T>::destroy(std::uint32_t n)
{
    FLUFFY_ASSERT(n < size(), "Request for undefined index in Pool");
    T* ptr = static_cast<T*>(get(n));
    ptr->~T();
}