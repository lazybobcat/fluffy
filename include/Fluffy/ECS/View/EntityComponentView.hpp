//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 20/05/17.
//

#ifndef FLUFFY_ENTITYCOMPONENTVIEW_HPP
#define FLUFFY_ENTITYCOMPONENTVIEW_HPP

#include <Fluffy/ECS/Entity.hpp>
#include <cstdio>

namespace Fluffy {
namespace ECS {

class EntityManager;

template <typename... Types>
class EntityComponentView
{
public:
    typedef std::bitset<ECS::MAX_COMPONENTS> ComponentMask;

    class Iterator
    {
    public:
        Iterator(EntityManager* manager, std::size_t index, ComponentMask mask);

        std::size_t index() const;
        bool        isEnd() const;
        bool test(std::size_t index) const;
        EntityManager* entityManager() const;
        Entity         get() const;
        Entity operator*() const;
        bool operator==(const Iterator& rhs) const;
        bool operator!=(const Iterator& rhs) const;
        Iterator& operator++();

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
}

#endif //FLUFFY_ENTITYCOMPONENTVIEW_HPP
