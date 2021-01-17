#pragma once

#include <fluffy/definitions.hpp>
#include <fluffy/profiling/frame_profiling.hpp>
#include <fluffy/profiling/rendering_profiling.hpp>
#include <fluffy/profiling/scope_profiling.hpp>
#include <fluffy/time/clock.hpp>

#include <array>
#include <chrono>
#include <utility>
#include <vector>

#ifdef FLUFFY_PROFILING_ACTIVE

namespace Fluffy {

class Profiler
{
public:
    static Profiler* get();
    static bool      ScopeProfiling;

public:
    // Scope profiling
    void startSession(ScopeProfiler::SessionType type);
    void endSession(ScopeProfiler::SessionType type);
    void startFrame();
    void endFrame();

    Ref<ScopeProfiler::SelfDestroyingScope> scope(const char* name);

    [[nodiscard]] std::array<ScopeProfiler::Session, ScopeProfiler::SessionType::TOTAL> getSessions() const;

    // FPS profiling
    void frameTime(Time lastFrameTime);

    [[nodiscard]] Time        getLastFrameTime() const;
    [[nodiscard]] const Time* getFrameTimeData() const;
    [[nodiscard]] std::size_t getFrameTimeCount() const;

    // Rendering profiling
    void drawCall();

    [[nodiscard]] int getDrawCalls() const;

    // Memory profiling
    [[nodiscard]] std::uint64_t getMemoryUsage() const;

private:
    ScopeProfiler     mScopeProfiler;
    FrameProfiler     mFrameProfiler;
    RenderingProfiler mRenderingProfiler;
};
}

#define COMBINE1(X, Y) X##Y
#define COMBINE(X, Y) COMBINE1(X, Y)
#define FLUFFY_PROFILE_START_SESSION(type) Fluffy::Profiler::get()->startSession(type)
#define FLUFFY_PROFILE_END_SESSION(type) Fluffy::Profiler::get()->endSession(type)
#define FLUFFY_PROFILE_FRAME() Fluffy::Profiler::get()->startFrame()
#define FLUFFY_PROFILE_END_FRAME() Fluffy::Profiler::get()->endFrame()
#define FLUFFY_PROFILE_SCOPE(name) auto COMBINE(scope, __LINE__) = Fluffy::Profiler::get()->scope(name)
#define FLUFFY_PROFILE_FUNCTION() FLUFFY_PROFILE_SCOPE(__FUNCSIG__)
#define FLUFFY_PROFILE_FRAME_TIME(time) Fluffy::Profiler::get()->frameTime(time)
#define FLUFFY_PROFILE_DRAW_CALL() Fluffy::Profiler::get()->drawCall()

#else

#define FLUFFY_PROFILE_START_SESSION(type)
#define FLUFFY_PROFILE_END_SESSION(type)
#define FLUFFY_PROFILE_FRAME()
#define FLUFFY_PROFILE_END_FRAME()
#define FLUFFY_PROFILE_SCOPE(name)
#define FLUFFY_PROFILE_FUNCTION()
#define FLUFFY_PROFILE_FRAME_TIME(time)
#define FLUFFY_PROFILE_DRAW_CALL()

#endif