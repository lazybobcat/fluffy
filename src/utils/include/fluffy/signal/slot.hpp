//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 12/11/17.
//

#pragma once

#include <functional>

namespace Fluffy {

template<typename... Args>
class Signal;

class Slot
{
public:
    struct Id
    {
        Id() = default;
        Id(std::uint64_t id);

        std::uint64_t id();

        bool operator==(const Id& other) const;
        bool operator!=(const Id& other) const;
        bool operator<(const Id& other) const;

    private:
        std::uint64_t mId = 0;
    };

public:
    Slot() = default;

    void disconnect();
    Id   id();

private:
    template<typename... Args>
    friend class Signal;

private:
    Slot(std::function<void(Id)>&& disconnectCallback, Id id);

private:
    Id                      mId;
    std::function<void(Id)> mDisconnectCallback;
    bool                    mInitialized = false;
};
}
