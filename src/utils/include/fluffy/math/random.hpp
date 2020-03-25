#pragma once

#include <fluffy/pch.hpp>

namespace Fluffy {

/**
 * Generate a random number of type T between 'min' and 'max' included
 *
 * int r = Fluffy::Utility::rand<int>(1, 100);
 * float r = Fluffy::Utility::rand<float>(1.f, 2.f);
 */
template<typename T>
T rand(T min, T max);
}

#include <fluffy/math/random.inl>
