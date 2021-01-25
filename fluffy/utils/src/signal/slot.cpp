#include <fluffy/signal/slot.hpp>

using namespace Fluffy;

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
        mInitialized = false;
    }
}

Slot::Id Slot::id()
{
    return mId;
}

Slot::operator Id() const
{
    return mId;
}
