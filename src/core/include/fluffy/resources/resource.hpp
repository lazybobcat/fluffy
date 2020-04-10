#pragma once

#include <fluffy/file/path.hpp>

namespace Fluffy {

template<typename Resource>
class ResourceHolder;

class Resource
{
public:
    typedef std::size_t Identifier;
    static Identifier   InvalidIdentifier;

public:
    Resource()          = default;
    virtual ~Resource() = default;

    virtual bool loadFromFile(const Path& path) = 0;
};

Resource::Identifier Resource::InvalidIdentifier = -1;
}
