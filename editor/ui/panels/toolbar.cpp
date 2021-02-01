#include "toolbar.hpp"
#include "ui/layout.hpp"
#include <fluffy/profiling/profiler.hpp>
#include <imgui.h>

using namespace Fluffy;

Toolbar::Toolbar(OpenedWindowTracker& tracker)
  : ImGuiElement()
  , mWindowTracker(tracker)
{
}

void Toolbar::customRender(RenderContext&)
{
    FLUFFY_PROFILE_FUNCTION();

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            ImGui::Separator();
            if (ImGui::MenuItem(ICON_FA_TIMES "  Exit")) {
                OnExit.emit();
            }
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
