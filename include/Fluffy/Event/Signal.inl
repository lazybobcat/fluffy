//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 12/11/17.
//

#include <Fluffy/Event/Signal.hpp>
#include <cassert>

using namespace Fluffy::Event;

template <typename... Args>
Slot Signal<Args...>::connect(std::function<void(Args...)> callback)
{
    Slot::Id id(++mNextId);
    mCallbacks.insert(std::make_pair(id, callback));

    Slot slot(std::move([=](Slot::Id slot_id) {
                  this->disconnect(slot_id);
              }),
              id);

    return slot;
}

template <typename... Args>
void Signal<Args...>::disconnect(Slot slot)
{
    assert(mCallbacks.find(slot.id()) != mCallbacks.end());

    mCallbacks.erase(slot.id());
}

template <typename... Args>
void Signal<Args...>::disconnect(Slot::Id id)
{
    assert(mCallbacks.find(id) != mCallbacks.end());

    mCallbacks.erase(id);
}

template <typename... Args>
void Signal<Args...>::emit(Args... args)
{
    for (auto pair : mCallbacks) {
        pair.second(args...);
    }
}
