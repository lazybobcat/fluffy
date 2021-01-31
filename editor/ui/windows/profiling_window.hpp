#pragma once

#include <fluffy/imgui/imgui_window.hpp>
#include <fluffy/profiling/profiler.hpp>

#ifdef FLUFFY_PROFILING_ACTIVE

namespace Fluffy {

struct ProfileReport
{
    std::array<ScopeProfiler::Session, ScopeProfiler::SessionType::TOTAL> sessions{};
    RenderingStats                                                        renderingStats;
    std::uint64_t                                                         memoryUsage = 0;
};

struct ProfilingWindowDefinition : public ImGuiWindowDefinition
{
    explicit ProfilingWindowDefinition(const char* title, bool* openControl = nullptr, ImGuiWindowFlags flags = 0);
    float refreshTimeInSeconds = 1.f;
};

class ProfilingWindow : public ImGuiWindow
{
public:
    explicit ProfilingWindow(const ProfilingWindowDefinition& properties);

    void               update(Time dt) override;
    void               pause();
    [[nodiscard]] bool isPaused() const;

protected:
    void customRender(RenderContext&) override;
    void begin() override;

private:
    void renderStats() const;
    void renderScopeChart();
    void renderWindowContextMenu();
    void renderPlotContextMenu(ScopeProfiler::SessionType type);

    static float fpsValueGetter(void* data, int idx);
    static void  scopeValueGetter(float* startTimestamp, float* endTimestamp, ImU8* level, const char** caption, const void* data, int idx);

private:
    ProfileReport mLastReport;
    Time          mLastReportTime = Time::Zero;
    int           mCorner         = 2;
    bool          mPaused         = false;
};
}

#endif