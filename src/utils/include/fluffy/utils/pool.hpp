#pragma once

#include <fluffy/pch.hpp>

namespace Fluffy {

class BasePool
{
public:
    virtual ~BasePool();
    virtual std::size_t size() const             = 0;
    virtual void*       get(std::uint32_t n)     = 0;
    virtual void        expand(std::uint32_t n)  = 0;
    virtual void        destroy(std::uint32_t n) = 0;
};

template<typename T>
class Pool : public BasePool
{
public:
    std::size_t size() const;

    void* get(std::uint32_t n);
    void  set(std::uint32_t n, T&& object);

    void expand(std::uint32_t n);
    void destroy(std::uint32_t n);

private:
    std::vector<T> mBlocks;
};

#include <fluffy/utils/pool.inl>
}
