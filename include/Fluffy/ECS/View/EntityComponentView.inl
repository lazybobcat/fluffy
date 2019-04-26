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
                                                  ComponentMask  mask)
  : mEntityManager(manager)
  , mIndex(index)
  , mMask(mask)
{
}

template <typename... Types>
std::size_t EntityComponentView<Types...>::Iterator::index() const
{
    return mIndex;
}

template <typename... Types>
bool EntityComponentView<Types...>::Iterator::isEnd() const
{
    return mIndex >= mEntityManager->size();
}

template <typename... Types>
EntityManager* EntityComponentView<Types...>::Iterator::entityManager() const
{
    return mEntityManager;
}

template <typename... Types>
Entity EntityComponentView<Types...>::Iterator::get() const
{
    if (isEnd()) {
        return Entity();
    }

    return mEntityManager->getEntity(mEntityManager->createEntityId(mIndex));
}

template <typename... Types>
Entity EntityComponentView<Types...>::Iterator::operator*() const
{
    return get();
}

template <typename... Types>
bool EntityComponentView<Types...>::Iterator::operator==(const Iterator& rhs) const
{
    return mEntityManager == rhs.mEntityManager && mMask == rhs.mMask &&
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
    do {
        ++mIndex;
    } while (!isEnd() && !test(mIndex));

    return *this;
}

template <typename... Types>
bool EntityComponentView<Types...>::Iterator::test(std::size_t index) const
{
    return (mEntityManager->mEntityComponentMask[index] & mMask) == mMask;
}

/**********************************************************************************************************************/

template <typename... Types>
EntityComponentView<Types...>::EntityComponentView(const Iterator& first, const Iterator& last)
  : mFirst(first)
  , mLast(last)
{
    if (mFirst != mLast && !mFirst.test(mFirst.mIndex)) {
        ++mFirst;
    }
}

template <typename... Types>
typename EntityComponentView<Types...>::Iterator EntityComponentView<Types...>::begin() const
{
    return mFirst;
}

template <typename... Types>
typename EntityComponentView<Types...>::Iterator EntityComponentView<Types...>::end() const
{
    return mLast;
}

template <typename... Types>
std::size_t EntityComponentView<Types...>::size() const {
    std::size_t s = 0;

    for (auto it = begin(); it != end(); ++it) {
        ++s;
    }

    return s;
}
