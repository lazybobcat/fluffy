//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 27/12/15.
//

#include <Fluffy/ECS/EntityManager.hpp>
#include <Fluffy/definitions.hpp>
#include <cassert>

using namespace Fluffy::ECS;

EntityManager::EntityManager()
: mNextRef(FLUFFY_ECS_FIRST_ID),
  mFreeRefs(),
  mEntities()
{
}

Entity::Ref EntityManager::createEntity()
{
    Entity::Ref ref;
    if(!mFreeRefs.empty()) {
        ref = mFreeRefs.top();
        mFreeRefs.pop();
    } else {
        ref = mNextRef++;
    }

    Entity::Ptr ent = std::make_shared<Entity>(ref, this);
    mEntities.insert(std::make_pair(ref, ent));

    return ref;
}

void EntityManager::removeEntity(Entity::Ref ref)
{
    assert(mEntities.find(ref) != mEntities.end());

    mEntities.erase(ref);
    mFreeRefs.push(ref);
}

Entity::WeakPtr EntityManager::entity(Entity::Ref ref) const
{
    try {
        return mEntities.at(ref);
    } catch(std::out_of_range) {
        return Entity::WeakPtr();
    }
}


void EntityManager::removeAllEntities()
{
    while(mEntities.size() > 0) {
        removeEntity(mEntities.begin()->first);
    }
}

void EntityManager::clear()
{
    mEntities.clear();
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