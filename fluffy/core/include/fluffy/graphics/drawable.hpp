#pragma once

#include <fluffy/graphics/render_states.hpp>

namespace Fluffy {

class Painter;

class Drawable
{
public:
    virtual ~Drawable() = default;

private:
    friend class Painter;

    virtual void draw(Painter& painter, RenderStates states) const = 0;
};
}
