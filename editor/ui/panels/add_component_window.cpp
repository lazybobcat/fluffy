#include "add_component_window.hpp"
#include <fluffy/scene/components.hpp>
#include <opengl_texture.hpp>

using namespace Fluffy;

AddComponentWindowDefinition::AddComponentWindowDefinition(ComponentRegistry& components, const char* title, bool* openControl, ImGuiWindowFlags flags)
  : ImGuiPanelDefinition({ title, openControl, flags })
  , components(components)
{
}

AddComponentWindow::AddComponentWindow(const AddComponentWindowDefinition& properties)
  : ImGuiPanel(properties)
  , mComponents(properties.components)
  , mOpened(properties.openControl)
  , mDefaultTitle(properties.title)
{
}

void AddComponentWindow::customRender(RenderContext& context)
{
    static float buttonSize = 32.f;
    static float halfButton = buttonSize / 2.f;
    ImVec2       windowSize = ImGui::GetContentRegionAvail();
    int          columns    = std::min(6, std::max(1, (int)windowSize.x / 100)); // between 1 and 6 columns depending on window width
    ImGui::Columns(columns, nullptr, false);
    int count = 0;
    for (auto& component : mComponents) {
        float  cellSize = ImGui::GetColumnWidth();
        ImVec2 cursor   = ImGui::GetCursorPos();
        ImGui::SetCursorPosX(cursor.x + cellSize / 2.f - halfButton - ImGui::GetStyle().ItemSpacing.x - ImGui::GetScrollX() - 4.5f);
        if (ImGui::ImageButton((void*)dynamic_cast<OpenglTexture2D&>(*component.icon).getRendererId(), ImVec2(buttonSize, buttonSize))) {
            if (mCurrentEntity != Entity::INVALID) {
                component.addComponentFct(mCurrentEntity);
            }
        }

        float textWidth = ImGui::CalcTextSize(component.name.c_str()).x;
        ImGui::SetCursorPosX(cursor.x + cellSize / 2.f - textWidth / 2.f - ImGui::GetStyle().ItemSpacing.x - ImGui::GetScrollX());
        ImGui::Text("%s", component.name.c_str());
        ++count;

        if (count > 0 && count % columns == 0) {
            ImGui::Columns(1);
            ImGui::Dummy(ImVec2(0, 10.f));
            ImGui::Columns(columns, nullptr, false);
        } else {
            ImGui::NextColumn();
        }
    }
    ImGui::Columns(1);
}

void AddComponentWindow::openForEntity(Entity entity)
{
    resize({ 500, 300 });
    if (entity.has<TagComponent>()) {
        auto& tag = entity.get<TagComponent>();
        setTitle(printString("Add component to {}", tag.tag));
    } else {
        setTitle(mDefaultTitle);
    }

    mCurrentEntity = entity;
    *mOpened       = true;
}
