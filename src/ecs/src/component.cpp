//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 21/05/17.
//

#include <fluffy/component.hpp>
#include <fluffy/utils/logger.hpp>

using namespace Fluffy;

BaseComponent::Family BaseComponent::mFamilyCounter = 0;

void BaseComponent::fail()
{
    Logger::log(Logger::LogType::Error, "You must not delete any component by hand.");
    //exit(CODE); // @todo exit codes
}