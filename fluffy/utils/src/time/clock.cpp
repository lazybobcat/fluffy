#include <fluffy/time/clock.hpp>

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