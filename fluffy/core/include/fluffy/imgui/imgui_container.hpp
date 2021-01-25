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

    void render() override;
    void update(Time dt) override;

protected:
    void customRender() override;

private:
    std::vector<Ref<ImGuiElement>> mChildren;
};
}