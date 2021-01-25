#include <fluffy/imgui/imgui_element.hpp>

using namespace Fluffy;

void ImGuiElement::render(RenderContext& context)
{
    if (isVisible()) {
        begin();
        customRender(context);
        end();
    }
}

void ImGuiElement::update(Time dt)
{
}

void ImGuiElement::onEvent(Event& event)
{
}

void ImGuiElement::begin()
{
}

void ImGuiElement::end()
{
}
