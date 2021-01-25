#pragma once

#include <fluffy/imgui/imgui_element.hpp>
#include <fluffy/pch.hpp>

namespace Fluffy {

class ImGuiContainer : public ImGuiElement
{
public:
    ImGuiContainer()          = default;
    virtual ~ImGuiContainer() = default;

    void pack(const Ref<ImGuiElement>& element);

    void render(RenderContext& context) override;
    void update(Time dt) override;
    void onEvent(Event& event) override;

protected:
    void customRender(RenderContext& context) override;

private:
    std::vector<Ref<ImGuiElement>> mChildren;
};
}