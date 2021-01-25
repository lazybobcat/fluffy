#include <fluffy/assert.hpp>
#include <fluffy/profiling/scope_profiling.hpp>
#include <thread>

using namespace Fluffy;

#ifdef FLUFFY_PROFILING_ACTIVE

ScopeProfiler::SelfDestroyingScope::SelfDestroyingScope(ScopeProfiler::Scope& scope, std::function<void()> callback)
  : mScope(scope)
  , mCallback(std::move(callback))
{
}

ScopeProfiler::SelfDestroyingScope::~SelfDestroyingScope()
{
    mScope.end = std::chrono::steady_clock::now();
    mCallback();
}

/**********************************************************************************************************************/

ScopeProfiler::ScopeProfiler()
{
    for (int i = 0; i < (int)SessionType::TOTAL; ++i) {
        mSessions[i].type = (SessionType)i;
    }
}

void ScopeProfiler::startSession(SessionType type)
{
    mSessions[type].type   = type;
    mSessions[type].start  = std::chrono::steady_clock::now();
    mSessions[type].thread = std::hash<std::thread::id>{}(std::this_thread::get_id());
}

void ScopeProfiler::endSession(ScopeProfiler::SessionType type)
{
    mSessions[type].end = std::chrono::steady_clock::now();
    // @todo Save session to file?
}

void ScopeProfiler::startFrame()
{
    auto threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
    for (auto& session : mSessions) {
        if (session.thread == threadID) {
            session.currentFrame.start = std::chrono::steady_clock::now();
            session.currentFrame.scopes.clear();
            break;
        }
    }
}

void ScopeProfiler::endFrame()
{
    auto threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
    for (auto& session : mSessions) {
        if (session.thread == threadID) {
            session.currentFrame.end = std::chrono::steady_clock::now();
            session.lastFrame.start  = session.currentFrame.start;
            session.lastFrame.end    = session.currentFrame.end;
            session.lastFrame.scopes = session.currentFrame.scopes;
            break;
        }
    }
}

Ref<ScopeProfiler::SelfDestroyingScope> ScopeProfiler::scope(const char* name)
{
    FLUFFY_ASSERT(mCurrentLevel < 255, "Too many scope levels!");
    Session* currentSession;
    auto     threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
    for (auto& session : mSessions) {
        if (session.thread == threadID) {
            currentSession = &session;
            break;
        }
    }
    Frame&      currentFrame = currentSession->currentFrame;
    Scope       scope;
    String      scopeName = name;
    std::size_t pos       = scopeName.find("__cdecl");
    if (pos != std::string::npos) {
        scopeName.erase(pos, 7);
    }
    scope.name  = scopeName;
    scope.start = std::chrono::steady_clock::now();
    scope.level = mCurrentLevel++;
    currentFrame.scopes.push_back(scope);
    Scope& currentScope = currentFrame.scopes.back();

    return CreateRef<SelfDestroyingScope>(currentScope, [&]() {
        mCurrentLevel--;
    });
}

#endif