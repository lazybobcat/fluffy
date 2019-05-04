//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright (c) 2019. All rights reserved.
// File created by loic on 04/05/2019.
//

#include <fluffy/context/context.hpp>

using namespace Fluffy;

Context::~Context()
{
    deInit();
}

void Context::init()
{
}

void Context::deInit()
{
}

std::unique_ptr<Context> Context::create()
{
    std::unique_ptr<Context> context(new Context());

    // @todo create and assign all parts of the context here

    return context;
}