//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 27/12/15.
//

#ifndef FLUFFY_ENTITYMANAGER_HPP
#define FLUFFY_ENTITYMANAGER_HPP

#include <Fluffy/ECS/Entity.hpp>
#include <Fluffy/Lua/Bindable.hpp>
#include <stack>
#include <map>

namespace Fluffy
{
namespace ECS
{

class EntityManager : public Lua::Bindable
{
public:
    EntityManager();

    Entity::Ref     createEntity();
    void            removeEntity(Entity::Ref ref);
    Entity::WeakPtr entity(Entity::Ref ref) const;

    void            removeAllEntities();
    void            clear();

    virtual void    bind(sel::State& state);

private:
    Entity::Ref mNextRef;
    std::stack<Entity::Ref> mFreeRefs;

    std::map<Entity::Ref,Entity::Ptr>   mEntities;
};

}
}

#endif //FLUFFY_ENTITYMANAGER_HPP
