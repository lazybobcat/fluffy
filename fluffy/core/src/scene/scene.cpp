#include <fluffy/ecs/components.hpp>
#include <fluffy/scene/scene.hpp>

using namespace Fluffy;
Scene::Scene(Context& context)
  : mEntityManager(*context.events)
{
}

Entity Scene::createEntity(const String& name)
{
    auto entity = mEntityManager.createEntity();
    entity.assign<TagComponent>(name);

    return entity;
}
void Scene::update(Time dt)
{
}

void Scene::render(RenderContext& context)
{
}

void Scene::onEvent(Event& event)
{
}
