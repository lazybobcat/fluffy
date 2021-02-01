#pragma once

#include <fluffy/imgui/imgui_element.hpp>
#include <fluffy/math/math.hpp>
#include <imgui.h>

namespace Fluffy {

struct ImGuiPanelDefinition
{
    const char*      title       = "";
    bool*            openControl = nullptr;
    ImGuiWindowFlags flags       = 0;
};

class ImGuiPanel : public ImGuiElement
{
public:
    explicit ImGuiPanel(const ImGuiPanelDefinition& properties);
    virtual ~ImGuiPanel() = default;

    void render(RenderContext& context) override;
    void show() override;
    void hide() override;
    void resize(const Vector2i& size);

protected:
    void begin() override;
    void end() override;

protected:
    const char*      mWindowTitle;
    bool*            mWindowOpenControl;
    ImGuiWindowFlags mWindowFlags;
    Vector2i         mWindowSize;

    bool mDefaultOpenControl = true;
    bool mNeedToResize       = false;
};
}