#pragma once

#include <fluffy/definitions.hpp>
#include <fluffy/imgui/imgui_window.hpp>

namespace Fluffy {

class AboutWindow : public ImGuiWindow
{
public:
    explicit AboutWindow(const ImGuiWindowDefinition& properties)
      : ImGuiWindow({ properties.title, properties.openControl, properties.flags })
    {
        resize({ 250, 240 });
    }

protected:
    void customRender() override
    {
        FLUFFY_PROFILE_SCOPE("ImGui About rendering");
        ImGui::TextColored(ImVec4(0.82f, 0.63f, 0.19f, 1.f), "Fluffy");
        ImGui::Text("Version %s", FLUFFY_VERSION);
        ImGui::Text("Created by Loïc Boutter");

        ImGui::Separator();
        ImGui::NewLine();
        ImGui::TextWrapped("Thank you for using Fluffy! This project would not have been possible without "
                    "awesome projects like Omar Cornut's Dear ImGui, STB, FMT and many others. Check them out!");

        ImGui::NewLine();
        ImGui::Separator();
        ImGui::Text("Published under WTFPL license");
    }
};
}
