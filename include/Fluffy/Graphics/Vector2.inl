//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 15/04/18.
//

#include <Fluffy/Graphics/Vector2.hpp>

using namespace Fluffy::Graphics;

template <typename T>
Vector2<T>::Vector2()
  : x(0)
  , y(0)
{
}

template <typename T>
Vector2<T>::Vector2(T x, T y)
  : x(x)
  , y(y)
{
}

template <typename T>
template <typename U>
Vector2<T>::Vector2(const Vector2<U>& other)
  : x(static_cast<T>(other.x))
  , y(static_cast<T>(other.y))
{
}

////////////////////////////////////////////////////////////

template <typename T>
inline Vector2<T> operator-(const Vector2<T>& right)
{
    return Vector2<T>(-right.x, -right.y);
}

template <typename T>
inline Vector2<T>& operator+=(Vector2<T>& left, const Vector2<T>& right)
{
    left.x += right.x;
    left.y += right.y;

    return left;
}

template <typename T>
inline Vector2<T>& operator-=(Vector2<T>& left, const Vector2<T>& right)
{
    left.x -= right.x;
    left.y -= right.y;

    return left;
}

template <typename T>
inline Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right)
{
    return Vector2<T>(left.x + right.x, left.y + right.y);
}

template <typename T>
inline Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right)
{
    return Vector2<T>(left.x - right.x, left.y - right.y);
}

template <typename T>
inline Vector2<T> operator*(const Vector2<T>& left, T right)
{
    return Vector2<T>(left.x * right, left.y * right);
}

template <typename T>
inline Vector2<T> operator*(T left, const Vector2<T>& right)
{
    return Vector2<T>(right.x * left, right.y * left);
}

template <typename T>
inline Vector2<T>& operator*=(Vector2<T>& left, T right)
{
    left.x *= right;
    left.y *= right;

    return left;
}

template <typename T>
inline Vector2<T> operator/(const Vector2<T>& left, T right)
{
    return Vector2<T>(left.x / right, left.y / right);
}

template <typename T>
inline Vector2<T>& operator/=(Vector2<T>& left, T right)
{
    left.x /= right;
    left.y /= right;

    return left;
}

template <typename T>
inline bool operator==(const Vector2<T>& left, const Vector2<T>& right)
{
    return (left.x == right.x) && (left.y == right.y);
}

template <typename T>
inline bool operator!=(const Vector2<T>& left, const Vector2<T>& right)
{
    return (left.x != right.x) || (left.y != right.y);
}