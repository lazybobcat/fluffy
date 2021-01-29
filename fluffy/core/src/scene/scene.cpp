#include <fluffy/scene/components.hpp>
#include <fluffy/scene/scene.hpp>

using namespace Fluffy;

Scene::Scene(Context& context)
{
    mRegistry = CreateRef<EntityRegistry>();
}

Entity Scene::createEntity(const String& name)
{
    auto entity = mRegistry->createEntity();
    entity.add<TagComponent>(name);

    return entity;
}

void Scene::removeEntity(Entity entity)
{
    mRegistry->destroy(entity);
}

EntityRegistry* Scene::getEntityRegistry() const
{
    return mRegistry.get();
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
