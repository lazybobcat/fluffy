#include "toolbar_window.hpp"
#include <fluffy/profiling/profiler.hpp>
#include <imgui.h>

using namespace Fluffy;

ToolbarWindow::ToolbarWindow(OpenedWindowTracker& tracker)
  : ImGuiElement()
  , mWindowTracker(tracker)
{
}

void ToolbarWindow::customRender(RenderContext&)
{
    FLUFFY_PROFILE_FUNCTION();

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Tools")) {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View")) {
            ImGui::MenuItem("Viewport", nullptr, &mWindowTracker.viewportWindowOpened);
            ImGui::MenuItem("Scene", nullptr, &mWindowTracker.sceneHierarchyWindowOpened);
            ImGui::MenuItem("Inspector", nullptr, &mWindowTracker.inspectorWindowOpened);
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
