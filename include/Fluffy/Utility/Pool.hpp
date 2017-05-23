//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 22/05/17.
//

#ifndef FLUFFY_POOL_HPP
#define FLUFFY_POOL_HPP

#include <cassert>
#include <cstdint>
#include <vector>

namespace Fluffy {
namespace Utility {

class BasePool
{
public:
    virtual ~BasePool();
    virtual std::size_t size() const      = 0;
    virtual void* get(std::uint32_t n)    = 0;
    virtual void expand(std::uint32_t n)  = 0;
    virtual void destroy(std::uint32_t n) = 0;
};

template <typename T>
class Pool : public BasePool
{
public:
    std::size_t size() const;

    void* get(std::uint32_t n);
    void set(std::uint32_t n, T&& object);

    void expand(std::uint32_t n);
    void destroy(std::uint32_t n);

private:
    std::vector<T> mBlocks;
};

#include <Fluffy/Utility/Pool.inl>
}
}

#endif //FLUFFY_POOL_HPP
