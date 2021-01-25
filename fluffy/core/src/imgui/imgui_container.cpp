#include <fluffy/imgui/imgui_container.hpp>
#include <fluffy/profiling/profiler.hpp>

using namespace Fluffy;

void ImGuiContainer::pack(const Ref<ImGuiElement>& element)
{
    mChildren.push_back(element);
}

void ImGuiContainer::render(RenderContext& context)
{
    FLUFFY_PROFILE_FUNCTION();

    for (const auto& child : mChildren) {
        child->render(context);
    }
}

void ImGuiContainer::update(Time dt)
{
    FLUFFY_PROFILE_FUNCTION();

    for (const auto& child : mChildren) {
        child->update(dt);
    }
}

void ImGuiContainer::onEvent(Event& event)
{
    FLUFFY_PROFILE_FUNCTION();

    for (const auto& child : mChildren) {
        child->onEvent(event);
    }
}

void ImGuiContainer::customRender(RenderContext&)
{
}
