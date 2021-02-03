#include <fluffy/imgui/imgui_panel.hpp>
#include <imgui.h>

using namespace Fluffy;

ImGuiPanel::ImGuiPanel(const ImGuiPanelDefinition& properties)
  : mWindowTitle(properties.title)
  , mWindowOpenControl(properties.openControl)
  , mWindowFlags(properties.flags)
{
    if (nullptr == mWindowOpenControl) {
        mWindowOpenControl = &mDefaultOpenControl;
    }
}

void ImGuiPanel::begin()
{
    if (mNeedToResize) {
        ImGui::SetNextWindowSize(ImVec2((float)mWindowSize.x, (float)mWindowSize.y));
        mNeedToResize = false;
    }
    ImGui::Begin(mWindowTitle.c_str(), mWindowOpenControl, mWindowFlags);
}

void ImGuiPanel::end()
{
    ImGui::End();
}

void ImGuiPanel::render(RenderContext& context)
{
    if (*mWindowOpenControl) {
        begin();
        customRender(context);
        end();
    }
}
void ImGuiPanel::show()
{
    ImGuiElement::show();
    *mWindowOpenControl = true;
}

void ImGuiPanel::hide()
{
    ImGuiElement::hide();
    *mWindowOpenControl = false;
}

void ImGuiPanel::resize(const Vector2i& size)
{
    mWindowSize   = size;
    mNeedToResize = true;
}

void ImGuiPanel::setTitle(const char* title)
{
    mWindowTitle = title;
}

void ImGuiPanel::setTitle(const String& title)
{
    mWindowTitle = title;
}
