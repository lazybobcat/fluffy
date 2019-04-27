//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 14/11/17.
//

#pragma once

#include <chrono>
#include <fluffy/time/time.hpp>

namespace Fluffy {

typedef std::chrono::time_point<std::chrono::steady_clock> TimePoint;

class Clock
{
public:
    Clock();

    Time elapsedTime() const;
    Time restart();

private:
    TimePoint mStartPoint;
};
}
