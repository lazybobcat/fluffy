//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 14/11/17.
//

#ifndef FLUFFY_CLOCK_HPP
#define FLUFFY_CLOCK_HPP

#include <Fluffy/Utility/Time.hpp>
#include <chrono>

namespace Fluffy {
namespace Utility {

typedef std::chrono::time_point<std::chrono::steady_clock> TimePoint;

class Clock
{
public:
    Clock();

    Time elapsedTime() const;
    Time restart();

private:
    TimePoint mStartPoint;
};
}
}

#endif //FLUFFY_CLOCK_HPP
