//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 12/11/17.
//

#include <Fluffy/Event/EventManager.hpp>

using namespace Fluffy::Event;

void EventManager::disconnect(Slot& slot)
{
    slot.disconnect();
}