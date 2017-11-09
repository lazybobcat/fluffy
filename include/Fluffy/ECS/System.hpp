//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 09/11/17.
//

#ifndef FLUFFY_SYSTEM_HPP
#define FLUFFY_SYSTEM_HPP

#include <Fluffy/ECS/EntityManager.hpp>
#include <Fluffy/Utility/NonCopyable.hpp>
#include <cstddef>

namespace Fluffy {
namespace ECS {

/**
 *  Base System - do not use this, inherit from System instead
 */
struct BaseSystem : Utility::NonCopyable
{
public:
    typedef std::size_t Family;

public:
    virtual ~BaseSystem() = default;

    virtual void configure(/**EventManager &eventManager**/);
    virtual void update(EntityManager& entityManager, /**EventManager &eventManager, **/ float dt) = 0;

protected:
    static Family mFamilyCounter;
};

template <typename Derived>
class System : public BaseSystem
{
public:
    virtual ~System() = default;

private:
    //    friend class SystemManager;
    static Family family()
    {
        static Family family = mFamilyCounter++;
        assert(family < ECS::MAX_COMPONENTS);

        return family;
    }
};
}
}

#endif //FLUFFY_SYSTEM_HPP
