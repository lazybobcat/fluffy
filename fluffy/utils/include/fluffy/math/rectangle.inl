#include <fluffy/math/rectangle.hpp>

using namespace Fluffy;

template<typename T>
Rect<T>::Rect()
  : left(0)
  , top(0)
  , width(0)
  , height(0)
{
}

template<typename T>
Rect<T>::Rect(T left, T top, T width, T height)
  : left(left)
  , top(top)
  , width(width)
  , height(height)
{
}

template<typename T>
Rect<T>::Rect(const glm::vec<2, T>& position, const glm::vec<2, T>& size)
  : left(position.x)
  , top(position.y)
  , width(size.x)
  , height(size.y)
{
}

template<typename T>
bool Rect<T>::contains(glm::vec<2, T> point) const
{
    T minX = std::min(left, static_cast<T>(left + width));
    T maxX = std::max(left, static_cast<T>(left + width));
    T minY = std::min(top, static_cast<T>(top + height));
    T maxY = std::max(top, static_cast<T>(top + height));

    return (point.x >= minX) && (point.x < maxX) && (point.y >= minY) && (point.y < maxY);
}

template<typename T>
bool Rect<T>::intersects(const Rect<T>& other) const
{
    Rect<T> intersection;
    return intersects(other, intersection);
}

template<typename T>
bool Rect<T>::intersects(const Rect<T>& other, Rect<T>& intersection) const
{
    T r1MinX = std::min(left, left + width);
    T r1MaxX = std::max(left, left + width);
    T r1MinY = std::min(top, top + height);
    T r1MaxY = std::max(top, top + height);

    T r2MinX = std::min(other.left, other.left + other.width);
    T r2MaxX = std::max(other.left, other.left + other.width);
    T r2MinY = std::min(other.top, other.top + other.height);
    T r2MaxY = std::max(other.top, other.top + other.height);

    // Intersection boundaries
    T interLeft   = std::max(r1MinX, r2MinX);
    T interTop    = std::max(r1MinY, r2MinY);
    T interRight  = std::min(r1MaxX, r2MaxX);
    T interBottom = std::min(r1MaxY, r2MaxY);

    // Intersection if we have a 'positive' inter rect
    if ((interLeft < interRight) && (interTop < interBottom)) {
        intersection = Rect<T>(interLeft, interTop, interRight - interLeft, interBottom - interTop);
        return true;
    } else {
        intersection = Rect<T>(0, 0, 0, 0);
        return false;
    }
}

template<typename T>
bool Rect<T>::operator==(const Rect<T>& rhs) const
{
    return left == rhs.left &&
           top == rhs.top &&
           width == rhs.width &&
           height == rhs.height;
}

template<typename T>
bool Rect<T>::operator!=(const Rect<T>& rhs) const
{
    return !(rhs == *this);
}
