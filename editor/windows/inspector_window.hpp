#pragma once

#include <fluffy/definitions.hpp>
#include <fluffy/imgui/imgui_panel.hpp>
#include <fluffy/scene/entity.hpp>

namespace Fluffy {

class InspectorWindow : public ImGuiWindow
{
public:
    Signal<> OnInspectedObjectChanged;

    Ref<Slot> EntitySelectedSlot;
    Ref<Slot> EntityUnselectedSlot;

public:
    explicit InspectorWindow(const ImGuiWindowDefinition& properties);

    void onEntitySelected(Entity entity);
    void onEntityUnselected();

protected:
    void customRender(RenderContext& context) override;

private:
    Entity mSelectedEntity = Entity::INVALID;
};
}
