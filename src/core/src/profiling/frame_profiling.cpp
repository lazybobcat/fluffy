#include <fluffy/profiling/frame_profiling.hpp>
#include <fluffy/time/time.hpp>

using namespace Fluffy;

#ifdef FLUFFY_PROFILING_ACTIVE
void FrameProfiler::push(Time time)
{
    mFrameTimes.push_back(time);
}

Time FrameProfiler::getAverage() const
{
    float totalMs = 0.f;
    int n = 0;

    for (const Time& time : mFrameTimes) {
        totalMs += time.milliseconds();
        ++n;
    }

    return milliseconds(totalMs / (float)n);
}

const Time* FrameProfiler::getData() const
{
    return mFrameTimes.data();
}

std::size_t FrameProfiler::count() const
{
    return mFrameTimes.size();
}
#endif