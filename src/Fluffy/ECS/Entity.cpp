//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 27/12/15.
//

#include <Fluffy/ECS/Entity.hpp>

using namespace Fluffy::ECS;
using namespace Fluffy::Utility;

Entity::Entity(Ref ref, EntityManager* em)
  : mRef(ref)
  , mManager(em)
{
}

Entity::~Entity()
{
    for (auto pair : mComponents) {
        delete pair.second;
    }
}

Entity::Ref Entity::getRef() const
{
    return mRef;
}

void Entity::serialize()
{
    serializeAttribute("ref", mRef);
}
