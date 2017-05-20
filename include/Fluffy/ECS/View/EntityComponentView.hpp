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
    class Iterator
    {
    public:
        Iterator(EntityManager* manager, std::size_t index, bool isEnd = false);

        std::size_t     getIndex() const;
        bool            isEnd() const;
        EntityManager*  getEntityManager() const;
        Entity::WeakPtr get() const;
        Entity::WeakPtr operator*() const;
        bool operator==(const Iterator& rhs) const;
        bool operator!=(const Iterator& rhs) const;
        Iterator& operator++();

    private:
        bool           mIsEnd;
        std::size_t    mIndex;
        EntityManager* mEntityManager;
    };

public:
    EntityComponentView(const Iterator& first, const Iterator& last);

    Iterator begin()
    {
        return mFirst;
    }

    Iterator end()
    {
        return mLast;
    }

private:
    Iterator mFirst;
    Iterator mLast;
};
}
}

#endif //FLUFFY_ENTITYCOMPONENTVIEW_HPP
