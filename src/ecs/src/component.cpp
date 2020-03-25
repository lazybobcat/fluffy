#include <fluffy/ecs/component.hpp>

using namespace Fluffy;

BaseComponent::Family BaseComponent::mFamilyCounter = 0;

void BaseComponent::fail()
{
    FLUFFY_LOG_ERROR("You must not delete any component by hand");

    exit(1); // @todo exit codes
}