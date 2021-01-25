#include <fluffy/ecs/entity.hpp>
#include <fluffy/ecs/entity_manager.hpp>

using namespace Fluffy;

const Entity::Id Entity::INVALID = Entity::Id();

Entity::Id::Id(const Id& other)
{
    mId = other.mId;
}

Entity::Id::Id(std::uint64_t id)
  : mId(id)
{
}

Entity::Id::Id(std::uint32_t index, std::uint32_t version)
  : mId(std::uint64_t(index) | std::uint64_t(version) << 32UL)
{
}

std::uint64_t Entity::Id::id() const
{
    return mId;
}

bool Entity::Id::operator==(const Id& other) const
{
    return mId == other.mId;
}

bool Entity::Id::operator!=(const Id& other) const
{
    return mId != other.mId;
}

bool Entity::Id::operator<(const Id& other) const
{
    return mId < other.mId;
}

std::uint32_t Entity::Id::index() const
{
    return mId & 0xffffffffUL;
}

std::uint32_t Entity::Id::version() const
{
    return mId >> 32;
}

/**********************************************************************************************************************/

Entity::Entity(EntityManager* em, Entity::Id id)
  : mManager(em)
  , mId(id)
{
}

Entity::Id Entity::id() const
{
    return mId;
}

bool Entity::isValid() const
{
    return mId != Entity::INVALID && mManager && mManager->isValid(mId);
}

void Entity::invalidate()
{
    mId = Entity::INVALID;
}

void Entity::destroy()
{
    FLUFFY_ASSERT(isValid(), "Entity is not valid");

    mManager->destroyEntity(mId);
    invalidate();
}

std::bitset<MAX_COMPONENTS> Entity::getComponentMask() const
{
    FLUFFY_ASSERT(isValid(), "Entity is not valid");

    return mManager->getComponentMask(mId);
}

Entity::operator bool() const
{
    return isValid();
}

bool Entity::operator==(const Entity& other) const
{
    return mManager == other.mManager && mId == other.mId;
}

bool Entity::operator!=(const Entity& other) const
{
    return !(*this == other);
}

bool Entity::operator<(const Entity& other) const
{
    return mId < other.mId;
}
