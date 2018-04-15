//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 15/04/18.
//

#include <Fluffy/Graphics/Vector3.hpp>

using namespace Fluffy::Graphics;

template <typename T>
Vector3<T>::Vector3()
  : x(0)
  , y(0)
  , z(0)
{
}

template <typename T>
Vector3<T>::Vector3(T x, T y, T z)
  : x(x)
  , y(y)
  , z(z)
{
}

template <typename T>
template <typename U>
Vector3<T>::Vector3(const Vector3<U>& other)
  : x(static_cast<T>(other.x))
  , y(static_cast<T>(other.y))
  , z(static_cast<T>(other.z))
{
}

////////////////////////////////////////////////////////////

template <typename T>
inline Vector3<T> operator-(const Vector3<T>& left)
{
    return Vector3<T>(-left.x, -left.y, -left.z);
}

template <typename T>
inline Vector3<T>& operator+=(Vector3<T>& left, const Vector3<T>& right)
{
    left.x += right.x;
    left.y += right.y;
    left.z += right.z;

    return left;
}

template <typename T>
inline Vector3<T>& operator-=(Vector3<T>& left, const Vector3<T>& right)
{
    left.x -= right.x;
    left.y -= right.y;
    left.z -= right.z;

    return left;
}

template <typename T>
inline Vector3<T> operator+(const Vector3<T>& left, const Vector3<T>& right)
{
    return Vector3<T>(left.x + right.x, left.y + right.y, left.z + right.z);
}

template <typename T>
inline Vector3<T> operator-(const Vector3<T>& left, const Vector3<T>& right)
{
    return Vector3<T>(left.x - right.x, left.y - right.y, left.z - right.z);
}

template <typename T>
inline Vector3<T> operator*(const Vector3<T>& left, T right)
{
    return Vector3<T>(left.x * right, left.y * right, left.z * right);
}

template <typename T>
inline Vector3<T> operator*(T left, const Vector3<T>& right)
{
    return Vector3<T>(right.x * left, right.y * left, right.z * left);
}

template <typename T>
inline Vector3<T>& operator*=(Vector3<T>& left, T right)
{
    left.x *= right;
    left.y *= right;
    left.z *= right;

    return left;
}

template <typename T>
inline Vector3<T> operator/(const Vector3<T>& left, T right)
{
    return Vector3<T>(left.x / right, left.y / right, left.z / right);
}

template <typename T>
inline Vector3<T>& operator/=(Vector3<T>& left, T right)
{
    left.x /= right;
    left.y /= right;
    left.z /= right;

    return left;
}

template <typename T>
inline bool operator==(const Vector3<T>& left, const Vector3<T>& right)
{
    return (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
}

template <typename T>
inline bool operator!=(const Vector3<T>& left, const Vector3<T>& right)
{
    return (left.x != right.x) || (left.y != right.y) || (left.z != right.z);
}