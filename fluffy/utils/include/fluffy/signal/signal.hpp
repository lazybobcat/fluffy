#pragma once

#include <fluffy/pch.hpp>
#include <fluffy/signal/slot.hpp>

namespace Fluffy {

template<typename... Args>
class Signal
{
public:
    Signal() = default;

    Slot connect(std::function<void(Args...)> callback);
    void disconnect(Slot slot);
    void disconnect(Slot::Id id);
    void emit(Args... args);

private:
    mutable std::map<Slot::Id, std::function<void(Args...)>> mCallbacks;
    mutable std::uint64_t                                    mNextId = 0;
};
}

#include <fluffy/signal/signal.inl>
