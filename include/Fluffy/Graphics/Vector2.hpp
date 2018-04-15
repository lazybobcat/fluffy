//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 15/04/18.
//

#ifndef FLUFFY_VECTOR2_HPP
#define FLUFFY_VECTOR2_HPP

namespace Fluffy {
namespace Graphics {

template <typename T>
class Vector2
{
public:
    Vector2();
    Vector2(T x, T y);

    template <typename U>
    explicit Vector2(const Vector2<U>& other);

public:
    T x;
    T y;
};

template <typename T>
Vector2<T> operator-(const Vector2<T>& right);

template <typename T>
Vector2<T>& operator+=(Vector2<T>& left, const Vector2<T>& right);

template <typename T>
Vector2<T>& operator-=(Vector2<T>& left, const Vector2<T>& right);

template <typename T>
Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right);

template <typename T>
Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right);

template <typename T>
Vector2<T> operator*(const Vector2<T>& left, T right);

template <typename T>
Vector2<T> operator*(T left, const Vector2<T>& right);

template <typename T>
Vector2<T>& operator*=(Vector2<T>& left, T right);

template <typename T>
Vector2<T> operator/(const Vector2<T>& left, T right);

template <typename T>
Vector2<T>& operator/=(Vector2<T>& left, T right);

template <typename T>
bool operator==(const Vector2<T>& left, const Vector2<T>& right);

#include <Fluffy/Graphics/Vector2.inl>

typedef Vector2<int>          Vector2i;
typedef Vector2<unsigned int> Vector2u;
typedef Vector2<float>        Vector2f;
}
}

#endif //FLUFFY_VECTOR2_HPP
