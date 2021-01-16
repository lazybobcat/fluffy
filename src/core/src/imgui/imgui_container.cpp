#include <fluffy/imgui/imgui_container.hpp>

using namespace Fluffy;

void ImGuiContainer::pack(const Ref<ImGuiElement>& element)
{
    mChildren.push_back(element);
}

void ImGuiContainer::render()
{
    for (const auto& child : mChildren) {
        child->render();
    }
}

void ImGuiContainer::update(Time dt)
{
    for (const auto& child : mChildren) {
        child->update(dt);
    }
}

void ImGuiContainer::customRender()
{
}
