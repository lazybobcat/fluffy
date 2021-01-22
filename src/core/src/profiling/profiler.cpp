#include <fluffy/profiling/memory_profiling.hpp>
#include <fluffy/profiling/profiler.hpp>
#include <json/json.h>

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
    std::unique_lock<std::mutex> lock(mMutex);
    mScopeProfiler.startSession(type);
}

void Profiler::endSession(ScopeProfiler::SessionType type)
{
    std::unique_lock<std::mutex> lock(mMutex);
    mScopeProfiler.endSession(type);
}

void Profiler::startFrame()
{
    std::unique_lock<std::mutex> lock(mMutex);
    mRenderingProfiler.reset();

    if (Profiler::ScopeProfiling) {
        mScopeProfiler.startFrame();
    }
}

void Profiler::endFrame()
{
    std::unique_lock<std::mutex> lock(mMutex);
    if (Profiler::ScopeProfiling) {
        mScopeProfiler.endFrame();
    }
}

void Profiler::saveToFile(ScopeProfiler::SessionType sessionType)
{
    std::unique_lock<std::mutex> lock(mMutex);

    std::ofstream file;
    file.open(FLUFFY_PROFILE_FILE, std::ios::trunc);
    if (file.is_open()) {
        Json::Value root;
        auto&       frame = mScopeProfiler.mSessions[(int)sessionType].lastFrame;
        for (auto& scope : frame.scopes) {
            auto timeStart = microseconds(std::chrono::duration_cast<std::chrono::microseconds>(scope.start - frame.start));
            auto timeEnd   = microseconds(std::chrono::duration_cast<std::chrono::microseconds>(scope.end - frame.start));

            Json::Value entry;
            entry["cat"]  = "function";
            entry["dur"]  = (int)(timeEnd - timeStart).microseconds();
            entry["name"] = scope.name;
            entry["ph"]   = "X";
            entry["pid"]  = "0";
            entry["tid"]  = mScopeProfiler.mSessions[(int)sessionType].thread;
            entry["ts"]   = (int)timeStart.microseconds();

            root["traceEvents"].append(entry);
        }
        file << root << std::endl;
        file.flush();
    }
    file.close();
}

Ref<ScopeProfiler::SelfDestroyingScope> Profiler::scope(const char* name)
{
    if (Profiler::ScopeProfiling) {
        std::unique_lock<std::mutex> lock(mMutex);
        return mScopeProfiler.scope(name);
    }

    return nullptr;
}

std::array<ScopeProfiler::Session, ScopeProfiler::SessionType::TOTAL> Profiler::getSessions() const
{
    return mScopeProfiler.mSessions;
}

std::uint64_t Profiler::getMemoryUsage() const
{
    return memory_usage;
}

void Profiler::drawCall(std::uint32_t nbVertices, std::uint32_t nbIndices)
{
    std::unique_lock<std::mutex> lock(mMutex);
    mRenderingProfiler.drawCall(nbVertices, nbIndices);
}

const RenderingStats& Profiler::getRenderingStats() const
{
    return mRenderingProfiler.getRenderingStats();
}

#endif