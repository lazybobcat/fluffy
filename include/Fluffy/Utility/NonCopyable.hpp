//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 27/12/15.
//

#ifndef FLUFFY_NONCOPYABLE_HPP
#define FLUFFY_NONCOPYABLE_HPP

namespace Fluffy {
namespace Utility {

class NonCopyable
{
protected:
    NonCopyable() = default;

private:
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};
}
}

#endif //FLUFFY_NONCOPYABLE_HPP
