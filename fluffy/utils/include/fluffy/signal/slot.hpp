#pragma once

#include <fluffy/pch.hpp>
#include <functional>

namespace Fluffy {

template<typename... Args>
class Signal;

class Slot
{
public:
    using Id = std::uint64_t;

public:
    Slot() = default;
    ~Slot();

    void disconnect();
    Id   id();

    operator Id() const;

private:
    template<typename... Args>
    friend class Signal;

private:
    Slot(std::function<void(Id)>&& disconnectCallback, Id id);

private:
    Id                      mId = 0;
    std::function<void(Id)> mDisconnectCallback;
    bool                    mInitialized = false;
};
}
