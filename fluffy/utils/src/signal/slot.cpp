#include <fluffy/signal/slot.hpp>

using namespace Fluffy;

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

Slot::~Slot()
{
    disconnect();
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