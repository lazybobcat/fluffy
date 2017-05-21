//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 27/12/15.
//

#include <Fluffy/ECS/EntityManager.hpp>
#include <Fluffy/ECS/Exception/EntityNotFoundException.hpp>
#include <Fluffy/Utility/String.hpp>
#include <Fluffy/definitions.hpp>
#include <algorithm>

using namespace Fluffy::ECS;
using namespace Fluffy::Utility;

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
    for (auto pool : mComponentPools) {
        delete pool;
    }
}

std::size_t EntityManager::size() const
{
    return mEntityComponentMask.size() - mFreeIndexes.size();
}

std::size_t EntityManager::capacity() const
{
    return mEntityComponentMask.size();
}

bool EntityManager::isValid(Entity::Id id) const
{
    return id.getIndex() < mEntityVersion.size() && mEntityVersion[id.getIndex()] == id.getVersion();
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

    // @todo event

    return entity;
}

void EntityManager::destroyEntity(Entity::Id id)
{
    assertValid(id);

    std::uint32_t index = id.getIndex();
    auto mask = mEntityComponentMask[index];

    for (std::size_t i = 0; i < mComponentHelpers.size(); ++i) {
        BaseComponentHelper* helper = mComponentHelpers[i];
        if (helper && mask.test(i)) {
            helper->removeComponent(Entity(this, id));
        }
    }

    // @todo event

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
        mEntityVersion.resize(index + 1);

        for (auto* pool : mComponentPools) {
            if (pool) {
                pool->expand(index + 1);
            }
        }
    }
}

void EntityManager::assertValid(Entity::Id id)
{
    assert(id.getIndex() < mEntityComponentMask.size());
    assert(id.getVersion() == mEntityVersion[id.getIndex()]);
}

Entity::Id EntityManager::createEntityId(std::uint32_t index) const
{
    return Entity::Id(index, mEntityVersion[index]);
}

//Entity::WeakPtr EntityManager::createEntity()
//{
//    Entity::Ref ref;
//    if (!mFreeRefs.empty()) {
//        ref = mFreeRefs.top();
//        mFreeRefs.pop();
//    } else {
//        ref = mNextRef++;
//    }
//
//    Entity::Ptr ent = std::make_shared<Entity>(ref, this);
//    mEntities.push_back(ent);
//    mEntitiesByRef.insert({ ref, ent });
//
//    return ent;
//}
//
//void EntityManager::removeEntity(Entity::WeakPtr entity)
//{
//    auto shared = entity.lock();
//    if (shared) {
//        mEntities.erase(std::remove(mEntities.begin(), mEntities.end(), shared), mEntities.end());
//        mEntitiesByRef.erase(shared->getRef());
//        mFreeRefs.push(shared->getRef());
//    }
//}
//
//Entity::WeakPtr EntityManager::entityByIndex(std::size_t index) const
//{
//    try {
//        return mEntities.at(index);
//    } catch (std::out_of_range) {
//        throw EntityNotFoundException(printString("No entity found in entity manager at index '%1'", { toString(index) }));
//    }
//}
//
//Entity::WeakPtr EntityManager::entity(Entity::Ref ref) const
//{
//    try {
//        return mEntitiesByRef.at(ref);
//    } catch (std::out_of_range) {
//        throw EntityNotFoundException(printString("No entity found in entity manager with reference #%1", { toString(ref) }));
//    }
//}
//
//void EntityManager::removeAllEntities()
//{
//    for (auto it = mEntities.begin(); it != mEntities.end(); ++it) {
//        removeEntity(*it);
//    }
//}
//
//void EntityManager::clear()
//{
//    mEntities.clear();
//    mEntitiesByRef.clear();
//    while (!mFreeRefs.empty())
//        mFreeRefs.pop();
//    mNextRef = FLUFFY_ECS_FIRST_ID;
//}
//
//std::size_t EntityManager::size() const
//{
//    return mEntities.size();
//}
//
//void EntityManager::bind(sel::State& state)
//{
//    state["CreateEntity"] = [this]() {
//        return createEntity();
//    };
//}