#pragma once

#include <fluffy/definitions.hpp>
#include <fluffy/time/clock.hpp>

#ifdef FLUFFY_PROFILING_ACTIVE

namespace Fluffy {

class Profiler;

namespace EnumNames {
const std::array<const char*, 2> SessionType({ { "Main thread", "Rendering thread" } });
}

class ScopeProfiler
{
public:
    static const std::uint8_t bufferSize = 255;

    struct Scope
    {
        TimePoint    start;
        TimePoint    end;
        String       name;
        std::uint8_t level = 0;
    };

    class SelfDestroyingScope
    {
    public:
        SelfDestroyingScope(Scope& scope, std::function<void()> callback);
        ~SelfDestroyingScope();

    private:
        Scope&                mScope;
        std::function<void()> mCallback;
    };

    struct Frame
    {
        TimePoint          start;
        TimePoint          end;
        std::vector<Scope> scopes = {};
    };

    enum SessionType
    {
        MainThread,
        RenderingThread,
        TOTAL
    };

    struct Session
    {
        SessionType        type = SessionType::MainThread;
        TimePoint          start;
        TimePoint          end;
        unsigned long long thread = 0;
        Frame              currentFrame;
        Frame              lastFrame;
    };

public:
    void startSession(SessionType type);
    void endSession(SessionType type);

    void startFrame();
    void endFrame();

    Ref<SelfDestroyingScope> scope(const char* name);

private:
    friend class Profiler;

private:
    std::array<Session, SessionType::TOTAL> mSessions;

    std::uint8_t mCurrentFrame = 0;
    std::uint8_t mCurrentLevel = 0;
};
}

#endif