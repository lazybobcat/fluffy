#include "inspector_window.hpp"
#include <fluffy/scene/components.hpp>

using namespace Fluffy;

InspectorWindow::InspectorWindow(const ImGuiWindowDefinition& properties)
  : ImGuiWindow(properties)
{
}

void InspectorWindow::customRender(RenderContext& context)
{
    static char buffer[128];

    if (mSelectedEntity == Entity::INVALID) {
        return;
    }

    if (mSelectedEntity.has<TagComponent>()) {
        auto& Ctag = mSelectedEntity.get<TagComponent>();
        memset(buffer, 0, sizeof(buffer));
#if WIN32
        strcpy_s(buffer, sizeof(buffer), Ctag.tag.c_str());
#else
        strcpy(buffer, Ctag.tag.c_str());
#endif
        if (ImGui::InputText("Tag", buffer, sizeof(buffer))) {
            Ctag.tag = String(buffer);
        }
    }

    if (mSelectedEntity.has<TransformComponent>()) {
        if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform")) {
            auto& Ctransform = mSelectedEntity.get<TransformComponent>();

            // Position
            auto pos = Ctransform.getPosition();
            if (ImGui::DragFloat3("Position", glm::value_ptr(pos), 1.f)) {
                Ctransform.setPosition(pos);
            }

            // Rotation
            auto rot = Ctransform.getEulerAngles();
            if (ImGui::DragFloat3("Rotation", glm::value_ptr(rot), 0.5f)) {
                Ctransform.setRotation(rot);
            }

            // Scale
            auto scale = Ctransform.getScale();
            if (ImGui::DragFloat3("Scale", glm::value_ptr(scale), 0.1f)) {
                Ctransform.setScale(scale);
            }

            ImGui::TreePop();
        }
    }
}

void InspectorWindow::onEntitySelected(Entity entity)
{
    mSelectedEntity = entity;
    OnInspectedObjectChanged.emit();
}

void InspectorWindow::onEntityUnselected()
{
    mSelectedEntity = Entity::INVALID;
    OnInspectedObjectChanged.emit();
}
