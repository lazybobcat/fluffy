#pragma once

#include <fluffy/assert.hpp>
#include <fluffy/pch.hpp>
#include <fluffy/signal/slot.hpp>

namespace Fluffy {

template<typename... Args>
class Signal
{
public:
    Signal() = default;

    Ref<Slot> connect(std::function<void(Args...)> callback)
    {
        Slot::Id id(++mNextId);
        auto     slot  = Ref<Slot>(new Slot(
          std::move([=, this](Slot::Id slot_id) {
              this->disconnect(slot_id);
          }),
          id));
        mCallbacks[id] = callback;

        return slot;
    }

    void disconnect(Slot::Id id)
    {
        FLUFFY_ASSERT(mCallbacks.find(id) != mCallbacks.end(), "Slot not found");

        mCallbacks.erase(id);
    }

    void emit(Args... args)
    {
        for (const auto& it : mCallbacks) {
            it.second(args...);
        }
    }

private:
    mutable std::map<Slot::Id, std::function<void(Args...)>> mCallbacks;
    mutable std::uint64_t                                    mNextId = 0;
};
}
