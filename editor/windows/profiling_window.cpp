#include "profiling_window.hpp"
#include <imgui_widget_flamegraph.h>

using namespace Fluffy;

#ifdef FLUFFY_PROFILING_ACTIVE

constexpr Vector2f SMALL_SIZE = Vector2f(300, 100);
constexpr Vector2f BIG_SIZE   = Vector2f(1080, 300);
constexpr float    DISTANCE   = 10.f;

ProfilingWindowDefinition::ProfilingWindowDefinition(const char* title, bool* openControl, ImGuiWindowFlags flags)
  : ImGuiWindowDefinition{ title, openControl, flags }
{
}

ProfilingWindow::ProfilingWindow(const ProfilingWindowDefinition& properties)
  : ImGuiWindow({ properties.title, properties.openControl, properties.flags })
{
    resize(SMALL_SIZE);
}

void ProfilingWindow::update(Time dt)
{
    FLUFFY_PROFILE_FUNCTION();

    mLastReportTime += dt;
    if (mLastReportTime > seconds(1.f)) {
        mLastReportTime = Time::Zero;
        auto profiler   = Profiler::get();
        if (!mPaused) {
            mLastReport.sessions = profiler->getSessions();
        }
        mLastReport.renderingStats = profiler->getRenderingStats();
        mLastReport.memoryUsage    = profiler->getMemoryUsage();
    }
}

void ProfilingWindow::begin()
{
    FLUFFY_PROFILE_FUNCTION();

    ImGuiIO& io  = ImGui::GetIO();
    mWindowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
    if (mCorner != -1) {
        mWindowFlags |= ImGuiWindowFlags_NoMove;
        ImGuiViewport* viewport         = ImGui::GetMainViewport();
        ImVec2         work_area_pos    = viewport->GetWorkPos(); // Instead of using viewport->Pos we use GetWorkPos() to avoid menu bars, if any!
        ImVec2         work_area_size   = viewport->GetWorkSize();
        ImVec2         window_pos       = ImVec2((mCorner & 1) ? (work_area_pos.x + work_area_size.x - DISTANCE) : (work_area_pos.x + DISTANCE), (mCorner & 2) ? (work_area_pos.y + work_area_size.y - DISTANCE) : (work_area_pos.y + DISTANCE));
        ImVec2         window_pos_pivot = ImVec2((mCorner & 1) ? 1.0f : 0.0f, (mCorner & 2) ? 1.0f : 0.0f);
        ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
        ImGui::SetNextWindowViewport(viewport->ID);
    }
    ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
    ImGuiWindow::begin();
}

void ProfilingWindow::customRender(RenderContext&)
{
    FLUFFY_PROFILE_FUNCTION();

    //    renderFpsChart();
    renderStats();
    ImGui::Separator();
    renderScopeChart();
    renderWindowContextMenu();
}

void ProfilingWindow::renderStats() const
{
    float fps = 1.f / mLastReport.renderingStats.frameTime.seconds();
    ImGui::Text("%.1f FPS (%.2fms/frame)", fps, mLastReport.renderingStats.frameTime.milliseconds());
    ImGui::Text("%d draw calls (%d vertices, %d indices)", mLastReport.renderingStats.drawCalls, mLastReport.renderingStats.verticesDrawn, mLastReport.renderingStats.indicesUsed);
    ImGui::Text("%.2fKB of memory tracked", mLastReport.memoryUsage / 1000.f);
}

void ProfilingWindow::renderScopeChart()
{
    ImGui::Checkbox("Display scope profiling", &Profiler::ScopeProfiling);

    if (Profiler::ScopeProfiling) {
        resize(BIG_SIZE);

        // Print one graph per session. A session should be tied to a thread.
        ImGui::BeginChild("Scope Profile Plots", ImVec2(0.f, 176.f), false);
        ImGui::BeginTabBar("Profiling##Tabs", ImGuiTabBarFlags_None | ImGuiTabBarFlags_NoCloseWithMiddleMouseButton);
        for (const auto& session : mLastReport.sessions) {
            if (ImGui::BeginTabItem(EnumNames::SessionType[(int)session.type])) {
                renderPlotContextMenu(session.type);
                if (!session.lastFrame.scopes.empty()) {
                    ImGuiWidgetFlameGraph::PlotFlame(&ProfilingWindow::scopeValueGetter,
                                                     &session.lastFrame,
                                                     (int)session.lastFrame.scopes.size(),
                                                     0,
                                                     EnumNames::SessionType[(int)session.type],
                                                     FLT_MAX,
                                                     FLT_MAX,
                                                     ImVec2(0.f, 150.f));
                }
                ImGui::EndTabItem();
            }
        }
        ImGui::EndTabBar();
        ImGui::EndChild();
    } else {
        resize(SMALL_SIZE);
    }
}

void ProfilingWindow::renderWindowContextMenu()
{
    if (ImGui::BeginPopupContextWindow()) {
        if (ImGui::MenuItem("Custom", nullptr, mCorner == -1))
            mCorner = -1;
        if (ImGui::MenuItem("Top-left", nullptr, mCorner == 0))
            mCorner = 0;
        if (ImGui::MenuItem("Top-right", nullptr, mCorner == 1))
            mCorner = 1;
        if (ImGui::MenuItem("Bottom-left", nullptr, mCorner == 2))
            mCorner = 2;
        if (ImGui::MenuItem("Bottom-right", nullptr, mCorner == 3))
            mCorner = 3;
        if (ImGui::MenuItem("Close"))
            *mWindowOpenControl = false;
        ImGui::EndPopup();
    }
}

void ProfilingWindow::renderPlotContextMenu(ScopeProfiler::SessionType type)
{
    if (ImGui::BeginPopupContextWindow()) {
        ImGui::MenuItem("(Drag 'scope_tracing.json' to chrome://tracing)", nullptr, false, false);
        if (ImGui::MenuItem("Print in file")) {
            Profiler::get()->saveToFile(type);
        }
        if (ImGui::MenuItem("Pause", nullptr, mPaused)) {
            pause();
        }
        ImGui::EndPopup();
    }
}

float ProfilingWindow::fpsValueGetter(void* data, int idx)
{
    Time* times = reinterpret_cast<Time*>(data);

    return 1.f / times[idx].seconds();
}

void ProfilingWindow::scopeValueGetter(float* startTimestamp, float* endTimestamp, ImU8* level, const char** caption, const void* data, int idx)
{
    auto  frame = reinterpret_cast<const ScopeProfiler::Frame*>(data);
    auto& scope = frame->scopes[idx];
    if (caption) {
        *caption = scope.name.c_str();
    }

    if (startTimestamp) {
        auto time       = microseconds(std::chrono::duration_cast<std::chrono::microseconds>(scope.start - frame->start));
        *startTimestamp = time.milliseconds();
    }

    if (endTimestamp) {
        auto time     = microseconds(std::chrono::duration_cast<std::chrono::microseconds>(scope.end - frame->start));
        *endTimestamp = time.milliseconds();
    }

    if (level) {
        *level = scope.level;
    }
}

void ProfilingWindow::pause()
{
    mPaused = !mPaused;
}

bool ProfilingWindow::isPaused() const
{
    return mPaused;
}

#endif