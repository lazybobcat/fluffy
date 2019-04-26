//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 27/12/15.
//

#include <Fluffy/ECS/EntityManager.hpp>
#include <algorithm>

using namespace Fluffy::ECS;
using namespace Fluffy::Utility;

EntityManager::EntityManager(EventManager& eventManager)
  : mEventManager(eventManager)
  , mEntityVersion()
  , mComponentPools()
  , mEntityComponentMask()
  , mComponentHelpers()
{
}

EntityManager::EntityManager(EventManager* eventManager)
  : mEventManager(*eventManager)
  , mEntityVersion()
  , mComponentPools()
  , mEntityComponentMask()
  , mComponentHelpers()
{
}

EntityManager::~EntityManager()
{
    reset();
}

std::size_t EntityManager::size() const
{
    return mEntityComponentMask.size() - mFreeIndexes.size();
}

std::size_t EntityManager::capacity() const
{
    return mEntityComponentMask.size();
}

void EntityManager::reset()
{
    while (mFreeIndexes.size() > 0) {
        mFreeIndexes.pop();
    }
    mEntityVersion.clear();
    mEntityComponentMask.clear();
    for (auto pool : mComponentPools) {
        delete pool;
    }
    mComponentPools.clear();
    for (auto helper : mComponentHelpers) {
        delete helper;
    }
    mComponentHelpers.clear();

    mIndexCounter = 0;
}

bool EntityManager::isValid(Entity::Id id) const
{
    return id.index() < mEntityVersion.size() && mEntityVersion[id.index()] == id.version();
}

Entity EntityManager::createEntity()
{
    std::uint32_t index;
    std::uint32_t version;

    if (mFreeIndexes.empty()) {
        index = mIndexCounter++;
        prepareForEntity(index);
        version = mEntityVersion[index] = 1;
    } else {
        index = mFreeIndexes.top();
        mFreeIndexes.pop();
        version = mEntityVersion[index];
    }

    Entity entity(this, Entity::Id(index, version));

    mEventManager.emit<EntityCreatedEvent>(EntityCreatedEvent(entity));

    return entity;
}

void EntityManager::destroyEntity(Entity::Id id)
{
    assertValid(id);

    std::uint32_t index = id.index();
    auto          mask  = mEntityComponentMask[index];

    for (std::size_t i = 0; i < mComponentHelpers.size(); ++i) {
        BaseComponentHelper* helper = mComponentHelpers[i];
        if (helper && mask.test(i)) {
            helper->removeComponent(Entity(this, id));
        }
    }

    mEventManager.emit<EntityDestroyedEvent>(EntityDestroyedEvent(Entity(this, id)));

    mEntityComponentMask[index].reset();
    mEntityVersion[index]++;
    mFreeIndexes.push(index);
}

Entity EntityManager::getEntity(Entity::Id id)
{
    assertValid(id);

    return Entity(this, id);
}

void EntityManager::prepareForEntity(std::uint32_t index)
{
    if (mEntityComponentMask.size() <= index) {
        mEntityComponentMask.resize(index + 1);

        for (auto* pool : mComponentPools) {
            if (pool) {
                pool->expand(index + 1);
            }
        }
    }

    if (mEntityVersion.size() <= index) {
        mEntityVersion.resize(index + 1);
    }
}

void EntityManager::assertValid(Entity::Id id) const
{
    assert(id.index() < mEntityComponentMask.size());
    assert(id.version() == mEntityVersion[id.index()]);
}

Entity::Id EntityManager::createEntityId(std::uint32_t index) const
{
    return Entity::Id(index, mEntityVersion[index]);
}

EntityManager::ComponentMask EntityManager::getComponentMask(Entity::Id id)
{
    assertValid(id);

    return mEntityComponentMask[id.index()];
}