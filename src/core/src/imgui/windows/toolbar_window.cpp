#include <fluffy/imgui/windows/toolbar_window.hpp>
#include <fluffy/profiling/profiler.hpp>
#include <imgui.h>

using namespace Fluffy;

ToolbarWindow::ToolbarWindow(OpenedWindowTracker& tracker)
  : ImGuiElement()
  , mWindowTracker(tracker)
{
}

void ToolbarWindow::customRender()
{
    FLUFFY_PROFILE_SCOPE("ImGui Toolbar rendering");
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Tools")) {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View")) {
#ifdef FLUFFY_PROFILING_ACTIVE
            ImGui::MenuItem("Profiling", nullptr, &mWindowTracker.profilingWindowOpened);
#endif
            ImGui::MenuItem("Logs", nullptr, &mWindowTracker.logsWindowOpened);
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help")) {
            ImGui::Separator();
            ImGui::MenuItem("About", nullptr, &mWindowTracker.aboutWindowOpened);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}
