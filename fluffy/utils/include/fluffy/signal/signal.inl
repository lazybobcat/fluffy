#include <fluffy/assert.hpp>
#include <fluffy/signal/signal.hpp>

using namespace Fluffy;

template<typename... Args>
Slot Signal<Args...>::connect(std::function<void(Args...)> callback)
{
    Slot::Id id(++mNextId);
    mCallbacks.insert(std::make_pair(id, callback));

    Slot slot(std::move([=, this](Slot::Id slot_id) {
                  this->disconnect(slot_id);
              }),
              id);

    return slot;
}

template<typename... Args>
void Signal<Args...>::disconnect(Slot slot)
{
    FLUFFY_ASSERT(mCallbacks.find(slot.id()) != mCallbacks.end(), "Slot not found");

    mCallbacks.erase(slot.id());
}

template<typename... Args>
void Signal<Args...>::disconnect(Slot::Id id)
{
    FLUFFY_ASSERT(mCallbacks.find(id) != mCallbacks.end(), "Slot not found");

    mCallbacks.erase(id);
}

template<typename... Args>
void Signal<Args...>::emit(Args... args)
{
    for (auto pair : mCallbacks) {
        pair.second(args...);
    }
}
