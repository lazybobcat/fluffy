#include "scene_hierarchy_window.hpp"
#include <fluffy/profiling/profiler.hpp>
#include <fluffy/scene/components.hpp>

using namespace Fluffy;

SceneHierarchyWindow::SceneHierarchyWindow(const SceneHierarchyWindowDefinition& properties)
  : ImGuiWindow({ properties.title, properties.openControl, properties.flags })
{
    setScene(properties.scene);
}

void SceneHierarchyWindow::customRender(RenderContext& context)
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
}

void SceneHierarchyWindow::drawEntityNode(Entity entity)
{
    auto Ctag = entity.get<TagComponent>();
    ImGuiTreeNodeFlags flags = ((mSelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
    bool opened = ImGui::TreeNodeEx((void*)(std::uint64_t)(std::uint32_t)entity, flags, "%s", Ctag.tag.c_str());
    if (ImGui::IsItemClicked()) {
        select(entity);
    }
    if (opened) {
        ImGui::TreePop();
    }
}

void SceneHierarchyWindow::setScene(const Ref<Scene>& scene)
{
    mScene = scene;
}

void SceneHierarchyWindow::select(Entity entity)
{
    auto registry = mScene->getEntityRegistry();
    if (registry->valid(entity)) {
        mSelectedEntity = entity;
        OnEntitySelected.emit(entity);
    }
}

void SceneHierarchyWindow::unselect()
{
    mSelectedEntity = {};
    OnEntityUnselected.emit();
}

Entity SceneHierarchyWindow::getSelectedEntity() const
{
    return mSelectedEntity;
}
