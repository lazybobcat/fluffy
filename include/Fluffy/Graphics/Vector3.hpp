//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 15/04/18.
//

#ifndef FLUFFY_VECTOR3_HPP
#define FLUFFY_VECTOR3_HPP

namespace Fluffy {
namespace Graphics {

template <typename T>
class Vector3
{
public:
    Vector3();
    Vector3(T x, T y, T z);

    template <typename U>
    explicit Vector3(const Vector3<U>& other);

public:
    T x;
    T y;
    T z;
};

template <typename T>
Vector3<T> operator-(const Vector3<T>& left);

template <typename T>
Vector3<T>& operator+=(Vector3<T>& left, const Vector3<T>& right);

template <typename T>
Vector3<T>& operator-=(Vector3<T>& left, const Vector3<T>& right);

template <typename T>
Vector3<T> operator+(const Vector3<T>& left, const Vector3<T>& right);

template <typename T>
Vector3<T> operator-(const Vector3<T>& left, const Vector3<T>& right);

template <typename T>
Vector3<T> operator*(const Vector3<T>& left, T right);

template <typename T>
Vector3<T> operator*(T left, const Vector3<T>& right);

template <typename T>
Vector3<T>& operator*=(Vector3<T>& left, T right);

template <typename T>
Vector3<T> operator/(const Vector3<T>& left, T right);

template <typename T>
Vector3<T>& operator/=(Vector3<T>& left, T right);

template <typename T>
bool operator==(const Vector3<T>& left, const Vector3<T>& right);

template <typename T>
bool operator!=(const Vector3<T>& left, const Vector3<T>& right);

#include <Fluffy/Graphics/Vector3.inl>

typedef Vector3<int>          Vector3i;
typedef Vector3<unsigned int> Vector3u;
typedef Vector3<float>        Vector3f;
}
}

#endif //FLUFFY_VECTOR3_HPP
