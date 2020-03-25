#pragma once

#include <fluffy/ecs/entity.hpp>
#include <fluffy/pch.hpp>

namespace Fluffy {

class EntityManager;

template<typename... Types>
class EntityComponentView
{
public:
    typedef std::bitset<MAX_COMPONENTS> ComponentMask;

    class Iterator
    {
    public:
        Iterator(EntityManager* manager, std::size_t index, ComponentMask mask);

        std::size_t    index() const;
        bool           isEnd() const;
        bool           test(std::size_t index) const;
        EntityManager* entityManager() const;
        Entity         get() const;
        Entity         operator*() const;
        bool           operator==(const Iterator& rhs) const;
        bool           operator!=(const Iterator& rhs) const;
        Iterator&      operator++();

    private:
        friend class EntityComponentView;

        EntityManager* mEntityManager;
        std::size_t    mIndex;
        ComponentMask  mMask;
    };

public:
    EntityComponentView(const Iterator& first, const Iterator& last);

    Iterator begin() const;
    Iterator end() const;

    // Avoid using this as it will iterate through the collection, for debugging purpose only
    std::size_t size() const;

private:
    Iterator mFirst;
    Iterator mLast;
};
}
