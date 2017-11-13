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
#include <Fluffy/Event/EventManager.hpp>
#include <Fluffy/Utility/NonCopyable.hpp>
#include <cstddef>

namespace Fluffy {
namespace ECS {

class SystemManager;

/**
 *  Base System - do not use this, inherit from System instead
 */
struct BaseSystem : Utility::NonCopyable
{
public:
    typedef std::size_t Family;

public:
    virtual ~BaseSystem() = default;

    virtual void configure(EntityManager& entityManager, EventManager& eventManager);
    virtual void update(EntityManager& entityManager, float dt) = 0;

protected:
    static Family mFamilyCounter;
};

/**
 * You should inherit from this class to create your own Systems
 *
 * struct RenderingSystem : public BaseSystem<RenderingSystem> {
 *     void update(EntityManager& entityManager, float dt) {
 *         // Do stuff
 *     }
 * }
 */
template <typename Derived>
class System : public BaseSystem
{
public:
    virtual ~System() = default;

private:
    friend class SystemManager;
    static Family family()
    {
        static Family family = mFamilyCounter++;

        return family;
    }
};
}
}

#endif //FLUFFY_SYSTEM_HPP
