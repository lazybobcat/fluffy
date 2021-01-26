#pragma once

#include <fluffy/api/context.hpp>
#include <fluffy/ecs/entity_manager.hpp>
#include <fluffy/graphics/render_context.hpp>

namespace Fluffy {

class Scene
{
public:
    explicit Scene(Context& context);

    Entity createEntity(const String& name = "Unnamed");
    template<typename... Components>
    EntityComponentView<Components...> each()
    {
        return std::move(mEntityManager.each<Components...>());
    }

    void update(Time dt);
    void render(RenderContext& context);
    void onEvent(Event& event);

private:
    EntityManager mEntityManager;
};
}