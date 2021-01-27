#pragma once

#include <fluffy/graphics/shape.hpp>

namespace Fluffy {

class RectangleShape : public Shape
{
public:
    explicit RectangleShape(const Vector2f& size);

    void     setSize(const Vector2f& size);
    Vector2f getSize() const;

    size_t   getVerticesCount() override { return 4; }
    Vector3f getVertexPosition(std::size_t index) override;

private:
    Vector2f mSize;
};
}