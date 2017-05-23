//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 27/12/15.
//

#include <Fluffy/ECS/Entity.hpp>
#include <Fluffy/ECS/EntityManager.hpp>

using namespace Fluffy::ECS;
using namespace Fluffy::Utility;

const Entity::Id Entity::INVALID = Entity::Id();

Entity::Id::Id(std::uint64_t id)
  : mId(id)
{
}

Entity::Id::Id(std::uint32_t index, std::uint32_t version)
  : mId(std::uint64_t(index) | std::uint64_t(version) << 32UL)
{

}

std::uint64_t Entity::Id::getId() const
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

std::uint32_t Entity::Id::getIndex() const
{
    return mId & 0xffffffffUL;
}

std::uint32_t Entity::Id::getVersion() const
{
    return mId >> 32;
}

/**********************************************************************************************************************/

Entity::Entity(EntityManager* em, Entity::Id id)
  : mManager(em)
  , mId(id)
{
}

Entity::Id Entity::getId() const
{
    return mId;
}

bool Entity::isValid() const
{
    return mManager && mManager->isValid(mId);
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
