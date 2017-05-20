//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 27/12/15.
//

#ifndef FLUFFY_ENTITY_HPP
#define FLUFFY_ENTITY_HPP

#include <Fluffy/ECS/Component.hpp>
#include <Fluffy/ECS/ComponentHandle.hpp>
#include <Fluffy/Utility/NonCopyable.hpp>
#include <Fluffy/Utility/Debuggable.hpp>
#include <cstdint>
#include <memory>
#include <string>
#include <typeindex>
#include <unordered_map>

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
    ~Entity();

    Ref             getRef() const;

    template <typename T, typename... Args>
    ComponentHandle<T> assign(Args&&... args);

    template <typename T>
    ComponentHandle<T> get();

    template <typename T>
    bool has() const;

    template <typename T, typename V, typename... Types>
    bool has() const;
    
    template <typename T>
    void remove();


    virtual void    serialize();

private:
    Ref             mRef;
    EntityManager*  mManager;
    std::unordered_map<std::type_index, Component*> mComponents;
};

}
}

#include <Fluffy/ECS/Entity.inl>

#endif //FLUFFY_ENTITY_HPP
