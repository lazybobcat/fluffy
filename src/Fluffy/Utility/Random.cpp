//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 16/11/17.
//

#include <Fluffy/Utility/Random.hpp>

using namespace Fluffy::Utility;

namespace {
std::random_device random_device;
std::seed_seq      seed({ random_device(), random_device(), random_device(), random_device(), random_device() });
std::mt19937       random_engine(seed);
}

template <typename T>
T Fluffy::Utility::rand(T min, T max)
{
    using distribution_type = typename std::conditional<
      std::is_integral<T>::value,
      std::uniform_int_distribution<T>,
      std::uniform_real_distribution<T>>::type;
    auto dist = distribution_type(min, max);

    return dist(random_engine);
}