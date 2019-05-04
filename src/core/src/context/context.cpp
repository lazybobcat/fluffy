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
    terminate();
}

void Context::initialize()
{
}

void Context::terminate()
{
}

std::unique_ptr<Context> Context::create()
{
    std::unique_ptr<Context> context(new Context());

    // @todo create and assign all parts of the context here

    return context;
}