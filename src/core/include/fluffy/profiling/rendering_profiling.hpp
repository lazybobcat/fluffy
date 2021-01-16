#pragma once

#include <fluffy/definitions.hpp>

#ifdef FLUFFY_PROFILING_ACTIVE

namespace Fluffy {

class RenderingProfiler
{
public:
    void drawCall(int count = 1);
    void reset();

    int getDrawCalls() const;

private:
    mutable int mDrawCalls          = 0;
    int         mLastFrameDrawCalls = 0;
};
}

#endif