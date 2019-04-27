//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 14/11/17.
//

#include <fluffy/clock.hpp>

using namespace Fluffy;

Clock::Clock()
{
    mStartPoint = std::chrono::steady_clock::now();
}

Time Clock::elapsedTime() const
{
    auto now = std::chrono::steady_clock::now();

    return microseconds(std::chrono::duration_cast<std::chrono::microseconds>(now - mStartPoint));
}

Time Clock::restart()
{
    auto elapsed_time = elapsedTime();

    mStartPoint = std::chrono::steady_clock::now();

    return elapsed_time;
}