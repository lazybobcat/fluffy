#include <fluffy/imgui/imgui_container.hpp>
#include <fluffy/profiling/profiler.hpp>

using namespace Fluffy;

void ImGuiContainer::pack(const Ref<ImGuiElement>& element)
{
    mChildren.push_back(element);
}

void ImGuiContainer::render()
{
    FLUFFY_PROFILE_FUNCTION();

    for (const auto& child : mChildren) {
        child->render();
    }
}

void ImGuiContainer::update(Time dt)
{
    FLUFFY_PROFILE_FUNCTION();

    for (const auto& child : mChildren) {
        child->update(dt);
    }
}

void ImGuiContainer::customRender()
{
}
