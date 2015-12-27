//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 27/12/15.
//

#include <Fluffy/Utility/Debuggable.hpp>
#include <Fluffy/definitions.hpp>

using namespace Fluffy::Utility;

std::string Debuggable::debug()
{
    serialize();

#if FLUFFY_DEBUG_COMPACT_JSON
    Json::FastWriter writer;
#else
    Json::StyledWriter writer;
#endif

    return writer.write(mSerialized);
}