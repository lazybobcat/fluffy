#pragma once

#include "registry/component_registry.hpp"
#include <fluffy/definitions.hpp>
#include <fluffy/imgui/imgui_panel.hpp>
#include <fluffy/scene/entity.hpp>

namespace Fluffy {

struct InspectorPanelWindowDefinition : public ImGuiPanelDefinition
{
    explicit InspectorPanelWindowDefinition(ComponentRegistry& components, const char* title, bool* openControl = nullptr, ImGuiWindowFlags flags = 0);

    ComponentRegistry& components;
};

class InspectorPanel : public ImGuiPanel
{
public:
    Signal<>       OnInspectedObjectChanged;
    Signal<Entity> OnAddComponentButtonPressed;

    Ref<Slot> EntitySelectedSlot;
    Ref<Slot> EntityUnselectedSlot;

public:
    explicit InspectorPanel(const InspectorPanelWindowDefinition& properties);

    void onEntitySelected(Entity entity);
    void onEntityUnselected();

protected:
    void customRender(RenderContext& context) override;
    void drawComponents();

private:
    Entity             mSelectedEntity = Entity::INVALID;
    ComponentRegistry& mComponents;
};
}
