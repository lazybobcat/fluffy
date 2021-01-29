#include <fluffy/scene/entity.hpp>

using namespace Fluffy;

Entity Entity::INVALID = Entity();

Entity::Entity(entt::entity handle, EntityRegistry* registry)
  : mEntity(handle)
  , mRegistry(registry)
{
}

Entity::operator bool() const
{
    return mEntity != entt::null;
}

Entity::operator entt::entity() const
{
    return mEntity;
}

Entity::operator std::uint32_t() const
{
    return (std::uint32_t)mEntity;
}

bool Entity::operator==(const Entity& other) const
{
    return mRegistry == other.mRegistry && mEntity == other.mEntity;
}

bool Entity::operator!=(const Entity& other) const
{
    return !(*this == other);
}
