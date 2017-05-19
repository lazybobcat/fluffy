//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 27/12/15.
//

#ifndef FLUFFY_ENTITY_HPP
#define FLUFFY_ENTITY_HPP

#include <Fluffy/Utility/NonCopyable.hpp>
#include <Fluffy/Utility/Debuggable.hpp>
#include <cstdint>
#include <string>
#include <memory>

namespace Fluffy
{
namespace ECS
{

class EntityManager;

class Entity : Fluffy::Utility::NonCopyable, public Fluffy::Utility::Debuggable
{
public:
    typedef std::shared_ptr<Entity> Ptr;
    typedef std::weak_ptr<Entity>   WeakPtr;
    typedef u_int32_t               Ref;
    friend class EntityManager;

public:
    Entity(Ref ref, EntityManager* em);

    Ref             getRef() const;

    virtual void    serialize();

private:
    Ref             mRef;
    EntityManager*  mManager;
};

}
}

#endif //FLUFFY_ENTITY_HPP
