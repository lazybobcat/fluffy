#pragma once

#include <entt/entt.hpp>

namespace Fluffy {

class Entity;

class EntityRegistry : public entt::registry
{
public:
    EntityRegistry() = default;

    Entity createEntity();
};
}