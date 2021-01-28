#include <fluffy/scene/entity.hpp>
#include <fluffy/scene/entity_registry.hpp>

using namespace Fluffy;

Entity EntityRegistry::createEntity()
{
    auto handle = create();

    return Entity(handle, this);
}
