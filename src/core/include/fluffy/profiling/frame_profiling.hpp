#pragma once

#include <circular_buffer.hpp>
#include <fluffy/time/time.hpp>

#ifdef FLUFFY_PROFILING_ACTIVE

namespace Fluffy {

class FrameProfiler
{
public:
    void push(Time time);

    [[nodiscard]] Time        getAverage() const;
    [[nodiscard]] const Time* getData() const;
    [[nodiscard]] std::size_t count() const;

private:
    jm::circular_buffer<Time, 100> mFrameTimes;
};
}

#endif