//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 16/11/17.
//

#pragma once

#include <random>

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

#include <fluffy/random.inl>
