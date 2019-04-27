//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 12/11/17.
//

#pragma once

#include <fluffy/signal/slot.hpp>
#include <functional>
#include <map>
#include <vector>

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
