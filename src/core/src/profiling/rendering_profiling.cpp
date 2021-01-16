#include <fluffy/profiling/rendering_profiling.hpp>

using namespace Fluffy;

#ifdef FLUFFY_PROFILING_ACTIVE

void RenderingProfiler::drawCall(int count)
{
    mDrawCalls += count;
}

void RenderingProfiler::reset()
{
    mLastFrameDrawCalls = mDrawCalls;
    mDrawCalls          = 0;
}

int RenderingProfiler::getDrawCalls() const
{
    return mLastFrameDrawCalls;
}

#endif