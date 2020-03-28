#include <fluffy/game/context.hpp>

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