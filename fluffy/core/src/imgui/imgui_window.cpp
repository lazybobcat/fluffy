#include <fluffy/imgui/imgui_window.hpp>
#include <imgui.h>

using namespace Fluffy;

ImGuiWindow::ImGuiWindow(const ImGuiWindowDefinition& properties)
  : mWindowTitle(properties.title)
  , mWindowOpenControl(properties.openControl)
  , mWindowFlags(properties.flags)
{
    if (nullptr == mWindowOpenControl) {
        mWindowOpenControl = &mDefaultOpenControl;
    }
}

void ImGuiWindow::begin()
{
    if (mNeedToResize) {
        ImGui::SetNextWindowSize(ImVec2((float)mWindowSize.x, (float)mWindowSize.y));
        mNeedToResize = false;
    }
    ImGui::Begin(mWindowTitle, mWindowOpenControl, mWindowFlags);
}

void ImGuiWindow::end()
{
    ImGui::End();
}

void ImGuiWindow::render(RenderContext& context)
{
    if (*mWindowOpenControl) {
        begin();
        customRender(context);
        end();
    }
}
void ImGuiWindow::show()
{
    ImGuiElement::show();
    *mWindowOpenControl = true;
}

void ImGuiWindow::hide()
{
    ImGuiElement::hide();
    *mWindowOpenControl = false;
}

void ImGuiWindow::resize(const Vector2i& size)
{
    mWindowSize   = size;
    mNeedToResize = true;
}
