//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 27/12/15.
//

#include <algorithm>
#include <Fluffy/definitions.hpp>
#include <Fluffy/ECS/EntityManager.hpp>
#include <Fluffy/Utility/String.hpp>
#include <Fluffy/ECS/Exception/EntityNotFoundException.hpp>

using namespace Fluffy::ECS;
using namespace Fluffy::Utility;

EntityManager::EntityManager()
: mNextRef(FLUFFY_ECS_FIRST_ID),
  mFreeRefs(),
  mEntities()
{
}

Entity::WeakPtr EntityManager::createEntity()
{
    Entity::Ref ref;
    if(!mFreeRefs.empty()) {
        ref = mFreeRefs.top();
        mFreeRefs.pop();
    } else {
        ref = mNextRef++;
    }

    Entity::Ptr ent = std::make_shared<Entity>(ref, this);
    mEntities.push_back(ent);
    mEntitiesByRef.insert({ref, ent});

    return ent;
}

void EntityManager::removeEntity(Entity::WeakPtr entity)
{
    auto shared = entity.lock();
    if (shared)
    {
        mEntities.erase(std::remove(mEntities.begin(), mEntities.end(), shared), mEntities.end());
        mEntitiesByRef.erase(shared->getRef());
        mFreeRefs.push(shared->getRef());
    }
}

Entity::WeakPtr EntityManager::entityByIndex(std::size_t index) const
{
    try {
        return mEntities.at(index);
    } catch(std::out_of_range) {
        throw EntityNotFoundException(printString("No entity found in entity manager at index '%1'", {toString(index)}));
    }
}

Entity::WeakPtr EntityManager::entity(Entity::Ref ref) const
{
    try {
        return mEntitiesByRef.at(ref);
    } catch(std::out_of_range) {
        throw EntityNotFoundException(printString("No entity found in entity manager with reference #%1", {toString(ref)}));
    }
}

void EntityManager::removeAllEntities()
{
    for (auto it = mEntities.begin(); it != mEntities.end(); ++it)
    {
        removeEntity(*it);
    }
}

void EntityManager::clear()
{
    mEntities.clear();
    mEntitiesByRef.clear();
    while(!mFreeRefs.empty()) mFreeRefs.pop();
    mNextRef = FLUFFY_ECS_FIRST_ID;
}

std::size_t EntityManager::size() const
{
    return mEntities.size();
}


void EntityManager::bind(sel::State &state)
{
    state["CreateEntity"] = [this]() {
        return createEntity();
    };
}