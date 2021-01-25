#include <fluffy/imgui/imgui_element.hpp>

using namespace Fluffy;

void ImGuiElement::render()
{
    if (isVisible()) {
        begin();
        customRender();
        end();
    }
}

void ImGuiElement::update(Time dt)
{
}

void ImGuiElement::begin()
{
}

void ImGuiElement::end()
{
}
