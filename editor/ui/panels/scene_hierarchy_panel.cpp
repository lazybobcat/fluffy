#include "scene_hierarchy_panel.hpp"
#include "ui/layout.hpp"
#include <fluffy/profiling/profiler.hpp>
#include <fluffy/scene/components.hpp>

using namespace Fluffy;

SceneHierarchyPanel::SceneHierarchyPanel(const SceneHierarchyPanelDefinition& properties)
  : ImGuiPanel({ properties.title, properties.openControl, properties.flags })
{
    setScene(properties.scene);
}

void SceneHierarchyPanel::customRender(RenderContext& context)
{
    FLUFFY_PROFILE_SCOPE("ImGui SceneHierarchy rendering");

    auto registry = mScene->getEntityRegistry();
    auto view     = registry->view<TagComponent>();
    for (auto entityId : view) {
        Entity entity(entityId, registry);
        drawEntityNode(entity);
    }

    if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()) {
        unselect();
    }

    if (ImGui::BeginPopupContextWindow(0, 1, false)) {
        if (ImGui::MenuItem(ICON_FA_HAMBURGER "  Add entity")) {
            mScene->createEntity("New empty entity");
        }

        ImGui::EndPopup();
    }
}

void SceneHierarchyPanel::drawEntityNode(Entity entity)
{
    auto               Ctag   = entity.get<TagComponent>();
    ImGuiTreeNodeFlags flags  = ((mSelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
    bool               opened = ImGui::TreeNodeEx((void*)(std::uint64_t)(std::uint32_t)entity, flags, "%s", Ctag.tag.c_str());
    if (ImGui::IsItemClicked()) {
        select(entity);
    }

    bool entityDeleted = false;
    if (ImGui::BeginPopupContextItem()) {
        if (ImGui::MenuItem(ICON_FA_CUBES "  Add component")) {
            OnOpenAddComponentDialog.emit(entity);
        }
        if (ImGui::MenuItem(ICON_FA_TRASH "  Remove entity")) {
            entityDeleted = true;
        }
        ImGui::Separator();
        if (ImGui::MenuItem(ICON_FA_HAMBURGER "  Add entity")) {
            mScene->createEntity();
        }

        ImGui::EndPopup();
    }

    if (opened) {
        ImGui::TreePop();
    }

    if (entityDeleted) {
        mScene->removeEntity(entity);
        if (mSelectedEntity == entity) {
            unselect();
        }
    }
}

void SceneHierarchyPanel::setScene(const Ref<Scene>& scene)
{
    mScene = scene;
}

void SceneHierarchyPanel::select(Entity entity)
{
    auto registry = mScene->getEntityRegistry();
    if (registry->valid(entity)) {
        mSelectedEntity = entity;
        OnEntitySelected.emit(entity);
    }
}

void SceneHierarchyPanel::unselect()
{
    if (mSelectedEntity != Entity::INVALID) {
        mSelectedEntity = Entity::INVALID;
        OnEntityUnselected.emit();
    }
}

Entity SceneHierarchyPanel::getSelectedEntity() const
{
    return mSelectedEntity;
}
