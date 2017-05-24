//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 27/12/15.
//

#ifndef FLUFFY_ENTITY_HPP
#define FLUFFY_ENTITY_HPP

#include <Fluffy/definitions.hpp>
#include <bitset>
#include <cstdint>
#include <typeindex>

namespace Fluffy {
namespace ECS {

constexpr std::size_t MAX_COMPONENTS = 64;

class EntityManager;
template <typename C>
class ComponentHandle;

class Entity
{
public:
    struct Id
    {
        Id() = default;
        Id(std::uint64_t id);
        Id(std::uint32_t index, std::uint32_t version);

        std::uint64_t getId() const;
        std::uint32_t getIndex() const;
        std::uint32_t getVersion() const;

        bool operator==(const Id& other) const;
        bool operator!=(const Id& other) const;
        bool operator<(const Id& other) const;

    private:
        friend class EntityManager;

    private:
        std::uint64_t mId = 0;
    };

    static const Id INVALID;

public:
    Entity() = default;
    Entity(EntityManager* manager, Entity::Id id);
    Entity(const Entity& other) = default;
    Entity& operator=(const Entity& other) = default;

    Id getId() const;

    bool isValid() const;
    operator bool() const;
    bool operator==(const Entity& other) const;
    bool operator!=(const Entity& other) const;
    bool operator<(const Entity& other) const;

    /**
     * Invalidate an entity but does not destroy it or its component.
     * To destroy an entity use destroy()
     */
    void invalidate();

    /**
     * Invalidate and destroy this entity and its component
     */
    void destroy();
//
//    std::bitset<ECS::MAX_COMPONENTS> getComponentMask() const;

    template <typename C, typename... Args>
    ComponentHandle<C> assign(Args&&... args);

    /**
     * @return ComponentHandle<C> The new component handle
     */
    template <typename C, typename... Args>
    ComponentHandle<C> replace(Args&&... args);

    template <typename C>
    void remove();

    template <typename C>
    ComponentHandle<C> getComponent();

//    template <typename... Components>
//    std::tuple<ComponentHandle<Components>...> getComponents();

    template <typename C>
    bool hasComponent() const;

private:
    EntityManager* mManager;
    Entity::Id     mId = INVALID;
};
}
}

#endif //FLUFFY_ENTITY_HPP
