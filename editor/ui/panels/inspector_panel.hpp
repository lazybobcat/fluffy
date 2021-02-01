#pragma once

#include <fluffy/definitions.hpp>
#include <fluffy/imgui/imgui_panel.hpp>
#include <fluffy/scene/entity.hpp>

namespace Fluffy {

class InspectorPanel : public ImGuiPanel
{
public:
    Signal<> OnInspectedObjectChanged;

    Ref<Slot> EntitySelectedSlot;
    Ref<Slot> EntityUnselectedSlot;

public:
    explicit InspectorPanel(const ImGuiPanelDefinition& properties);

    void onEntitySelected(Entity entity);
    void onEntityUnselected();

protected:
    void customRender(RenderContext& context) override;
    void drawComponents();

private:
    Entity mSelectedEntity = Entity::INVALID;
};
}
