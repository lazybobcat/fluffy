//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 12/11/17.
//

#include <Fluffy/Event/Slot.hpp>

using namespace Fluffy::Event;

Slot::Id::Id(std::uint64_t id)
  : mId(id)
{
}

std::uint64_t Slot::Id::id()
{
    return mId;
}

bool Slot::Id::operator==(const Id& other) const
{
    return mId == other.mId;
}

bool Slot::Id::operator!=(const Id& other) const
{
    return mId != other.mId;
}

bool Slot::Id::operator<(const Id& other) const
{
    return mId < other.mId;
}

/**********************************************************************************************************************/

Slot::Slot(std::function<void(Slot::Id)>&& disconnectCallback, Slot::Id id)
  : mId(id)
  , mDisconnectCallback(disconnectCallback)
  , mInitialized(true)
{
}

void Slot::disconnect()
{
    if (mInitialized) {
        mDisconnectCallback(mId);
    }
}

Slot::Id Slot::id()
{
    return mId;
}