//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 23/05/17.
//

#include <fluffy/pool.hpp>

using namespace Fluffy;

template <typename T>
std::size_t Pool<T>::size() const
{
    return mBlocks.size();
}

template <typename T>
void* Pool<T>::get(std::uint32_t n)
{
    assert(n < size());
    T object = mBlocks[n];

    return &mBlocks[n];
}

template <typename T>
void Pool<T>::set(std::uint32_t n, T&& object)
{
    assert(n < size());
    mBlocks[n] = std::move(object);
}

template <typename T>
void Pool<T>::expand(std::uint32_t n)
{
    mBlocks.resize(n);
}

template <typename T>
void Pool<T>::destroy(std::uint32_t n)
{
    assert(n < size());
    T* ptr = static_cast<T*>(get(n));
    ptr->~T();
}