//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 22/05/17.
//

#include <Fluffy/Utility/Pool.hpp>

using namespace Fluffy::Utility;

template <typename T>
std::size_t Pool<T>::size() const
{
    return mBlocks.size();
}

template <typename T>
void* Pool<T>::get(std::uint32_t n)
{
    assert(n < size());

    return &mBlocks[n];
}

template <typename T>
void Pool<T>::expand(std::uint32_t n)
{
    mBlocks.reserve(n);
}

template <typename T>
void Pool<T>::destroy(std::uint32_t n)
{
    assert(n < size());
    T* ptr = static_cast<T*>(get(n));
    ptr->~T();
}