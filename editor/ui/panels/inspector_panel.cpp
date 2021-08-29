#include "inspector_panel.hpp"
#include "ui/layout.hpp"
#include <fluffy/scene/components.hpp>

using namespace Fluffy;

InspectorPanelWindowDefinition::InspectorPanelWindowDefinition(ComponentRegistry& components, const char* title, bool* openControl, ImGuiWindowFlags flags)
  : ImGuiPanelDefinition({ title, openControl, flags })
  , components(components)
{
}

InspectorPanel::InspectorPanel(const InspectorPanelWindowDefinition& properties)
  : ImGuiPanel(properties)
  , mComponents(properties.components)
{
}

void InspectorPanel::customRender(RenderContext& context)
{
    if (mSelectedEntity == Entity::INVALID) {
        return;
    }

    drawComponents();
}

void InspectorPanel::drawComponents()
{
    static char buffer[128];

    if (mSelectedEntity.has<TagComponent>()) {
        auto& Ctag = mSelectedEntity.get<TagComponent>();
        memset(buffer, 0, sizeof(buffer));
#if WIN32
        strcpy_s(buffer, sizeof(buffer), Ctag.tag.c_str());
#else
        strcpy(buffer, Ctag.tag.c_str());
#endif

        // Add component button
        if (ImGui::Button(ICON_FA_CUBES)) {
            OnAddComponentButtonPressed.emit(mSelectedEntity);
        }
        ImGui::SameLine();
        if (ImGui::InputText("##Tag", buffer, sizeof(buffer))) {
            Ctag.tag = String(buffer);
        }
    }

    for (auto& component : mComponents) {
        component.drawComponentFct(mSelectedEntity);
    }
}

void InspectorPanel::onEntitySelected(Entity entity)
{
    mSelectedEntity = entity;
    OnInspectedObjectChanged.emit();
}

void InspectorPanel::onEntityUnselected()
{
    mSelectedEntity = Entity::INVALID;
    OnInspectedObjectChanged.emit();
}
