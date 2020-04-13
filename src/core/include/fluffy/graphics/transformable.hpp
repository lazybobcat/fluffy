#pragma once

#include <fluffy/graphics/transform.hpp>

namespace Fluffy {

class Transformable
{
public:
    Transformable()          = default;
    virtual ~Transformable() = default;

    // @todo tmp
    Transform transform;

private:
};
}
