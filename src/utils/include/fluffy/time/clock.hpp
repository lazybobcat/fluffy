#pragma once

#include <fluffy/pch.hpp>
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
