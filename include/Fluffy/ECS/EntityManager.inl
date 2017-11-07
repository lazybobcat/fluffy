//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 21/05/17.
//

#include <Fluffy/ECS/EntityManager.hpp>

using namespace Fluffy::ECS;
using namespace Fluffy::Utility;

template <typename C>
std::size_t EntityManager::componentFamily()
{
    return Component<typename std::remove_const<C>::type>::getFamily();
}

template <typename C, typename... Args>
ComponentHandle<C> EntityManager::assign(Entity::Id id, Args&&... args)
{
    assertValid(id);
    const BaseComponent::Family family = componentFamily<C>();
    assert(!mEntityComponentMask[id.index()].test(family));

    Pool<C>* pool = getComponentPool<C>();
    C        comp = C(std::forward<Args>(args)...);
    pool->set(id.index(), std::move(comp));

    ComponentHandle<C> component(this, id);
    mEntityComponentMask[id.index()].set(family);

    // @todo emit event

    return component;
};

template <typename C>
void EntityManager::remove(Entity::Id id)
{
    assertValid(id);
    const BaseComponent::Family family = componentFamily<C>();
    assert(mEntityComponentMask[id.index()].test(family));

    BasePool* pool = mComponentPools[family];

    ComponentHandle<C> component(this, id);
    // @todo emit event component about to be deleted including the ComponentHandle

    mEntityComponentMask[id.index()].reset(family);
    pool->destroy(id.index());
};

template <typename C>
bool EntityManager::hasComponent(Entity::Id id) const
{
    assertValid(id);
    const BaseComponent::Family family = componentFamily<C>();

    if (family > mComponentPools.size()) {
        return false;
    }

    BasePool* pool = mComponentPools[family];

    return (pool && mEntityComponentMask[id.index()][family]);
}

template <typename C>
ComponentHandle<C> EntityManager::component(Entity::Id id)
{
    assertValid(id);
    const BaseComponent::Family family = componentFamily<C>();

    if (family > mComponentPools.size()) {
        return ComponentHandle<C>();
    }

    BasePool* pool = mComponentPools[family];
    if (!pool || !mEntityComponentMask[id.index()][family]) {
        return ComponentHandle<C>();
    }

    ComponentHandle<C> component(this, id);
    return component;
}

template <typename... Components>
std::tuple<ComponentHandle<Components>...> EntityManager::components(Entity::Id id)
{
    return std::make_tuple(component<Components>(id)...);
}

template <typename... Components>
EntityComponentView<Components...> EntityManager::each()
{
    ComponentMask mask = getComponentMask<Components...>();

    typename EntityComponentView<Components...>::Iterator first(this, 0, mask);
    typename EntityComponentView<Components...>::Iterator last(this, size(), mask);

    return EntityComponentView<Components...>(first, last);
}

// Private

template <typename C>
C* EntityManager::getComponentPointer(Entity::Id id)
{
    BasePool* pool = mComponentPools[componentFamily<C>()];
    assert(pool);

    return static_cast<C*>(pool->get(id.index()));
}

template <typename C>
Pool<C>* EntityManager::getComponentPool()
{
    BaseComponent::Family family = componentFamily<C>();
    if (mComponentPools.size() <= family) {
        mComponentPools.resize(family + 1, nullptr);
    }
    if (!mComponentPools[family]) {
        Pool<C>* pool = new Pool<C>;
        pool->expand(mIndexCounter);
        mComponentPools[family] = pool;

        return pool;
    }

    if (mComponentHelpers.size() < family) {
        mComponentHelpers.resize(family + 1, nullptr);
    }
    if (!mComponentHelpers[family]) {
        ComponentHelper<C>* helper = new ComponentHelper<C>();
        mComponentHelpers[family]  = helper;
    }

    return static_cast<Pool<C>*>(mComponentPools[family]);
}

template <typename C>
EntityManager::ComponentMask EntityManager::getComponentMask()
{
    ComponentMask mask;
    mask.set(componentFamily<C>());

    return mask;
}

template <typename C1, typename C2, typename... Components>
EntityManager::ComponentMask EntityManager::getComponentMask()
{
    return getComponentMask<C1>() | getComponentMask<C2, Components...>();
}