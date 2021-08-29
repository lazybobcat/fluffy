#pragma once

#include "registry/component_registry.hpp"
#include <fluffy/imgui/imgui_panel.hpp>

namespace Fluffy {

struct AddComponentWindowDefinition : public ImGuiPanelDefinition
{
    explicit AddComponentWindowDefinition(ComponentRegistry& components, const char* title, bool* openControl = nullptr, ImGuiWindowFlags flags = 0);

    ComponentRegistry& components;
};

class AddComponentWindow : public ImGuiPanel
{
public:
    explicit AddComponentWindow(const AddComponentWindowDefinition& properties);

    void openForEntity(Entity entity);

protected:
    void customRender(RenderContext& context) override;

private:
    ComponentRegistry& mComponents;
    bool*              mOpened;
    String             mDefaultTitle;
    Entity             mCurrentEntity = Entity::INVALID;
};
}