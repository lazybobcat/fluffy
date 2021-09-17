#pragma once

#include <fluffy/api/context.hpp>
#include <fluffy/graphics/render_context.hpp>
#include <fluffy/scene/components.hpp>
#include <fluffy/scene/entity.hpp>
#include <fluffy/scene/entity_registry.hpp>

namespace Fluffy {

class Scene
{
public:
    explicit Scene(Context& context);

    virtual void initialize() {}
    virtual void terminate() {}

    Entity          createEntity(const String& name = "Unnamed");
    void            removeEntity(Entity entity);
    EntityRegistry* getEntityRegistry() const;

    void update(Time dt);
    void render(RenderContext& context);
    void onEvent(Event& event);
    void onTargetResize(const Vector2u& size);

protected:
    CameraComponent* getActiveCamera() const;

private:
    friend class Entity;

private:
    Ref<EntityRegistry> mRegistry;
};
}