#pragma once

#include <fluffy/ecs/component.hpp>
#include <fluffy/ecs/entity.hpp>
#include <fluffy/ecs/view/entity_component_view.hpp>
#include <fluffy/event/event_manager.hpp>
#include <fluffy/utils/pool.hpp>
#include <stack>
#include <typeindex>
#include <vector>

namespace Fluffy {

class EntityManager
{
public:
    typedef std::bitset<MAX_COMPONENTS> ComponentMask;

public:
    EntityManager(EventManager& eventManager);
    EntityManager(EventManager* eventManager);
    virtual ~EntityManager();

    /**
     * How many entities are handled
     */
    std::size_t size() const;
    std::size_t capacity() const;
    void        reset();

    bool isValid(Entity::Id id) const;

    Entity     createEntity();
    void       destroyEntity(Entity::Id id);
    Entity     getEntity(Entity::Id id);
    Entity::Id createEntityId(std::uint32_t index) const;

    template<typename C>
    static std::size_t componentFamily();

    template<typename C, typename... Args>
    ComponentHandle<C> assign(Entity::Id id, Args&&... args);

    template<typename C>
    void remove(Entity::Id id);

    template<typename C>
    bool hasComponent(Entity::Id id) const;

    template<typename C>
    ComponentHandle<C> component(Entity::Id id);

    template<typename... Components>
    std::tuple<ComponentHandle<Components>...> components(Entity::Id id);

    template<typename... Components>
    EntityComponentView<Components...> each();

private:
    void prepareForEntity(std::uint32_t index);
    void assertValid(Entity::Id id) const;

    template<typename C>
    C* getComponentPointer(Entity::Id id);

    template<typename C>
    Pool<C>* getComponentPool();

    ComponentMask getComponentMask(Entity::Id id);
    template<typename C>
    ComponentMask getComponentMask();
    template<typename C1, typename C2, typename... Components>
    ComponentMask getComponentMask();

private:
    friend class Entity;
    template<typename C>
    friend class ComponentHandle;
    template<typename... Types>
    friend class EntityComponentView;

    EventManager&                     mEventManager;
    std::uint32_t                     mIndexCounter = 0;
    std::stack<std::uint32_t>         mFreeIndexes;
    std::vector<std::uint32_t>        mEntityVersion;
    std::vector<BasePool*>            mComponentPools; // indexed by Component::family()
    std::vector<ComponentMask>        mEntityComponentMask;
    std::vector<BaseComponentHelper*> mComponentHelpers;
};
}

#include <fluffy/ecs/component_handle.inl>
#include <fluffy/ecs/entity.inl>
#include <fluffy/ecs/entity_manager.inl>
#include <fluffy/ecs/view/entity_component_view.inl>
