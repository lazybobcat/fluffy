//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 20/05/17.
//

#ifndef FLUFFY_COMPONENT_HPP
#define FLUFFY_COMPONENT_HPP

#include "ComponentHandle.hpp"
#include <cassert>
#include <memory>

namespace Fluffy {
namespace ECS {

/**
 *  Base Component - do not use this, inherit from Component instead
 */
struct BaseComponent
{
public:
    typedef std::size_t Family;

public:
    void operator delete(void* p) { fail(); }
    void operator delete[](void* p) { fail(); }

protected:
    static void fail();

    static Family mFamilyCounter;
};

/**
 * Must provide a default constructor
 *
 * Usage :
 *  struct Position : public Component<Position> {
 *      Position() : x(0), y(0) {}
 *
 *      float x, y;
 *  }
 */
template <typename Derived>
struct Component : public BaseComponent
{
public:
    typedef ComponentHandle<Derived>       Handle;
    typedef ComponentHandle<const Derived> ConstHandle;

private:
    friend class EntityManager;

    static std::size_t getFamily()
    {
        static std::size_t family = mFamilyCounter++;
        assert(family < ECS::MAX_COMPONENTS);

        return family;
    }
};

class BaseComponentHelper
{
public:
    virtual ~BaseComponentHelper()              = default;
    virtual void removeComponent(Entity entity) = 0;
};

template <typename C>
class ComponentHelper : public BaseComponentHelper
{
public:
    void removeComponent(Entity entity) override
    {
        entity.remove<C>();
    }
};
}
}

#endif //FLUFFY_COMPONENT_HPP
