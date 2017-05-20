//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 21/05/17.
//

#include <Fluffy/ECS/EntityManager.hpp>
#include <Fluffy/ECS/View/EntityComponentView.hpp>

using namespace Fluffy::ECS;

template <typename... Types>
EntityComponentView<Types...>::Iterator::Iterator(EntityManager* manager,
                                                  std::size_t    index,
                                                  bool           isEnd)
  : mEntityManager(manager)
  , mIndex(index)
  , mIsEnd(isEnd)
{
    if (mIndex >= manager->size()) {
        mIsEnd = true;
    }
}

template <typename... Types>
std::size_t EntityComponentView<Types...>::Iterator::getIndex() const
{
    return mIndex;
}

template <typename... Types>
bool EntityComponentView<Types...>::Iterator::isEnd() const
{
    return mIsEnd || mIndex >= mEntityManager->size();
}

template <typename... Types>
EntityManager* EntityComponentView<Types...>::Iterator::getEntityManager() const
{
    return mEntityManager;
}

template <typename... Types>
Entity::WeakPtr EntityComponentView<Types...>::Iterator::get() const
{
    if (isEnd()) {
        return Entity::WeakPtr();
    }

    return mEntityManager->entityByIndex(mIndex);
}

template <typename... Types>
Entity::WeakPtr EntityComponentView<Types...>::Iterator::operator*() const
{
    return get();
}

template <typename... Types>
bool EntityComponentView<Types...>::Iterator::operator==(const Iterator& rhs) const
{
    return mEntityManager == rhs.mEntityManager && mIsEnd == rhs.mIsEnd &&
           mIndex == rhs.mIndex;
}

template <typename... Types>
bool EntityComponentView<Types...>::Iterator::operator!=(const Iterator& rhs) const
{
    return !(*this == rhs);
}

template <typename... Types>
typename EntityComponentView<Types...>::Iterator& EntityComponentView<Types...>::Iterator::operator++()
{
    ++mIndex;
    while (mIndex < mEntityManager->size()) {
        auto weakEntity = get();
        if (!weakEntity.expired()) {
            auto entity = weakEntity.lock();
            if (entity->template has<Types...>()) {
                break;
            }
        }
        ++mIndex;
    }

    if (mIndex >= mEntityManager->size()) {
        mIsEnd = true;
    }

    return *this;
}

/**********************************************************************************************************************/

template <typename... Types>
EntityComponentView<Types...>::EntityComponentView(const Iterator& first, const Iterator& last)
  : mFirst(first)
  , mLast(last)
{
    if (mFirst.get().expired()) {
        ++mFirst;
    } else {
        auto weakEntity = mFirst.get();
        auto entity     = weakEntity.lock();
        if (!entity->template has<Types...>()) {
            ++mFirst;
        }
    }
}
