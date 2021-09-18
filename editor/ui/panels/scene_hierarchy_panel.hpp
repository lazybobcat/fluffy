#pragma once

#include <fluffy/definitions.hpp>
#include <fluffy/imgui/imgui_panel.hpp>
#include <fluffy/scene/scene.hpp>

namespace Fluffy {

struct SceneHierarchyPanelDefinition
{
    const char*      title       = "";
    bool*            openControl = nullptr;
    ImGuiWindowFlags flags       = 0;
    Ref<Scene>       scene;
};

class SceneHierarchyPanel : public ImGuiPanel
{
public:
    Signal<Entity> OnEntitySelected;
    Signal<>       OnEntityUnselected;
    Signal<Entity> OnOpenAddComponentDialog;

public:
    explicit SceneHierarchyPanel(const SceneHierarchyPanelDefinition& properties);

    void setScene(const Ref<Scene>& scene);
    void select(Entity entity);
    void unselect();

    Entity getSelectedEntity() const;

protected:
    void customRender(RenderContext& context) override;

private:
    void drawEntityNode(Entity entity);

private:
    Ref<Scene> mScene;
    Entity     mSelectedEntity = Entity::INVALID;
};
}
