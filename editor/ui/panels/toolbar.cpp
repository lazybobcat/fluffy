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
            if (ImGui::MenuItem(ICON_FA_FILE_MEDICAL "  New scene", "Ctrl+N")) {
                OnNewScene.emit();
            }
            if (ImGui::MenuItem(ICON_FA_FOLDER_OPEN "  Open...", "Ctrl+O")) {
                OnOpen.emit();
            }
            if (ImGui::MenuItem(ICON_FA_SAVE "  Save", "Ctrl+S")) {
                OnSave.emit();
            }
            if (ImGui::MenuItem(ICON_FA_SAVE "  Save as...", "Ctrl+Shift+S")) {
                OnSaveAs.emit();
            }
            ImGui::Separator();
            if (ImGui::MenuItem(ICON_FA_TIMES "  Exit", "Ctrl+Q")) {
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
