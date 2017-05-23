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

        std::size_t    getIndex() const;
        bool           isEnd() const;
        EntityManager* getEntityManager() const;
        Entity         get() const;
        Entity operator*() const;
        bool operator==(const Iterator& rhs) const;
        bool operator!=(const Iterator& rhs) const;
        Iterator& operator++();

    private:
        EntityManager* mEntityManager;
        std::size_t    mIndex;
        ComponentMask  mMask;
    };

public:
    EntityComponentView(const Iterator& first, const Iterator& last);

    Iterator begin();
    Iterator end();

private:
    Iterator mFirst;
    Iterator mLast;
};
}
}

#endif //FLUFFY_ENTITYCOMPONENTVIEW_HPP
