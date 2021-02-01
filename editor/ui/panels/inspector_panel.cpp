#include "inspector_panel.hpp"
#include "ui/layout.hpp"
#include <fluffy/scene/components.hpp>

using namespace Fluffy;

InspectorPanel::InspectorPanel(const ImGuiPanelDefinition& properties)
  : ImGuiPanel(properties)
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

        if (ImGui::Button(ICON_FA_CUBES)) {
            // @todo open a window listing all components in components registry
        }
        ImGui::SameLine();
        if (ImGui::InputText("##Tag", buffer, sizeof(buffer))) {
            Ctag.tag = String(buffer);
        }
    }

    Layout::drawComponent<TransformComponent>(mSelectedEntity, "Transform", [&]() {
        auto& Ctransform = mSelectedEntity.get<TransformComponent>();

        // Position
        auto pos = Ctransform.getPosition();
        Layout::drawXYZ("Translation", pos);
        Ctransform.setPosition(pos);

        // Rotation
        auto rot = Ctransform.getEulerAngles();
        Layout::drawXYZ("Rotation", rot, 0.f, 0.5f);
        Ctransform.setRotation(rot);

        // Scale
        auto scale = Ctransform.getScale();
        Layout::drawXYZ("Scale", scale, 1.f, 0.1f);
        Ctransform.setScale(scale);
    });

    Layout::drawComponent<SpriteComponent>(mSelectedEntity, "Sprite", [&]() {
        auto& Csprite = mSelectedEntity.get<SpriteComponent>();
        auto  color   = Csprite.rectangle.getFillColor().value;
        if (Layout::drawColorPicker("Color", color)) {
            Csprite.rectangle.setFillColor(color);
        }
    });
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
