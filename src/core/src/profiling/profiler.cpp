#include <fluffy/profiling/memory_profiling.hpp>
#include <fluffy/profiling/profiler.hpp>

using namespace Fluffy;

#ifdef FLUFFY_PROFILING_ACTIVE

bool Profiler::ScopeProfiling = false;

Profiler* Profiler::get()
{
    static Profiler instance;

    return &instance;
}

void Profiler::startSession(ScopeProfiler::SessionType type)
{
    mScopeProfiler.startSession(type);
}

void Profiler::endSession(ScopeProfiler::SessionType type)
{
    mScopeProfiler.endSession(type);
}

void Profiler::startFrame()
{
    mRenderingProfiler.reset();

    if (Profiler::ScopeProfiling) {
        mScopeProfiler.startFrame();
    }
}

void Profiler::endFrame()
{
    if (Profiler::ScopeProfiling) {
        mScopeProfiler.endFrame();
    }
}

Ref<ScopeProfiler::SelfDestroyingScope> Profiler::scope(const char* name)
{
    if (Profiler::ScopeProfiling) {
        return mScopeProfiler.scope(name);
    }

    return nullptr;
}

std::array<ScopeProfiler::Session, ScopeProfiler::SessionType::TOTAL> Profiler::getSessions() const
{
    return mScopeProfiler.mSessions;
}

void Profiler::frameTime(Time lastFrameTime)
{
    mFrameProfiler.push(lastFrameTime);
}

Time Profiler::getLastFrameTime() const
{
    return mFrameProfiler.getAverage();
}

const Time* Profiler::getFrameTimeData() const
{
    return mFrameProfiler.getData();
}

std::size_t Profiler::getFrameTimeCount() const
{
    return mFrameProfiler.count();
}

std::uint64_t Profiler::getMemoryUsage() const
{
    return memory_usage;
}

void Profiler::drawCall()
{
    mRenderingProfiler.drawCall();
}

int Profiler::getDrawCalls() const
{
    return mRenderingProfiler.getDrawCalls();
}

#endif