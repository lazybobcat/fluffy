#include <fluffy/profiling/rendering_profiling.hpp>

using namespace Fluffy;

#ifdef FLUFFY_PROFILING_ACTIVE

void RenderingProfiler::drawCall(std::uint32_t nbVertices, std::uint32_t nbIndices, int count)
{
    mStats.drawCalls += count;
    mStats.verticesDrawn += nbVertices;
    mStats.indicesUsed += nbIndices;
}

void RenderingProfiler::reset()
{
    mLastFrameStats = mStats;
    mStats.drawCalls = 0;
    mStats.verticesDrawn = 0;
    mStats.indicesUsed = 0;
}

const RenderingStats& RenderingProfiler::getRenderingStats() const
{
    return mLastFrameStats;
}

#endif