#include <fluffy/math/rectangle.hpp>

using namespace Fluffy;

Vector2f Fluffy::transformPoint(const glm::mat4& transform, const Vector2f& point)
{
    Vector4f p = Vector4f(point.x, point.y, 0.f, 1.f) * transform;

    return { p.x, p.y };
}

FloatRect Fluffy::transformRect(const glm::mat4& transform, const FloatRect& rect)
{
    const Vector2f points[] = {
        Fluffy::transformPoint(transform, { rect.left, rect.top }),
        Fluffy::transformPoint(transform, { rect.left, rect.top + rect.height }),
        Fluffy::transformPoint(transform, { rect.left + rect.width, rect.top }),
        Fluffy::transformPoint(transform, { rect.left + rect.width, rect.top + rect.height })
    };

    // Compute the bounding rectangle of the transformed points
    float left   = points[0].x;
    float top    = points[0].y;
    float right  = points[0].x;
    float bottom = points[0].y;
    for (int i = 1; i < 4; ++i) {
        if (points[i].x < left)
            left = points[i].x;
        else if (points[i].x > right)
            right = points[i].x;
        if (points[i].y < top)
            top = points[i].y;
        else if (points[i].y > bottom)
            bottom = points[i].y;
    }

    return FloatRect(left, top, right - left, bottom - top);
}