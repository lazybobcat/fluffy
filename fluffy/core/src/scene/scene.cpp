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
    CameraComponent* camera = getActiveCamera();

    if (camera) {
        context.with(*camera->camera).bind([&](Painter& painter) {
            painter.clear(Color::fromInt8(43, 43, 43, 255));
            // draw scene
            auto view = getEntityRegistry()->view<TransformComponent, SpriteComponent>();
            for (auto [entity, transform, sprite] : view.each()) {
                RenderStates states;
                states.transform = transform.getTransformMatrix();
                painter.drawSprite(sprite.sprite, states);
            }
        });
    } else {
        context.bind([&](Painter& painter) {
            painter.clear(Color::fromInt8(43, 43, 43, 255));
        });
    }
}

void Scene::onEvent(Event& event)
{
    if (Event::WindowResized == event.type) {
        onTargetResize(event.size.size);
    }
}

CameraComponent* Scene::getActiveCamera() const
{
    auto view = getEntityRegistry()->view<CameraComponent>();
    for (auto [entity, camera] : view.each()) {
        return &camera;
    }

    return nullptr;
}

void Scene::onTargetResize(const Vector2u& size)
{
    CameraComponent* camera = getActiveCamera();

    if (camera && !camera->fixedAspectRatio) {
        camera->camera->setTargetSize({ size.x * 1.f, size.y * 1.f });
    }
}
