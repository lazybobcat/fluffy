#pragma once

#include <fluffy/definitions.hpp>

#ifdef FLUFFY_PROFILING_ACTIVE

namespace Fluffy {

struct RenderingStats
{
    std::uint32_t drawCalls     = 0;
    std::uint32_t verticesDrawn = 0;
    std::uint32_t indicesUsed   = 0;
};

class RenderingProfiler
{
public:
    void drawCall(std::uint32_t nbVertices, std::uint32_t nbIndices, int count = 1);
    void reset();

    const RenderingStats& getRenderingStats() const;

private:
    mutable RenderingStats mStats;
    RenderingStats         mLastFrameStats;
};
}

#endif