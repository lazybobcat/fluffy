//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 09/11/17.
//

#pragma once

#include <cstddef>
#include <fluffy/entity_manager.hpp>
#include <fluffy/event/event_manager.hpp>
#include <fluffy/time/time.hpp>

namespace Fluffy {

class SystemManager;

/**
 *  Base System - do not use this, inherit from System instead
 */
struct BaseSystem
{
public:
    typedef std::size_t Family;

public:
    virtual ~BaseSystem() = default;

    virtual void initialize(EntityManager& entityManager, EventManager& eventManager);
    virtual void terminate(EntityManager& entityManager, EventManager& eventManager);
    virtual void update(EntityManager& entityManager, Fluffy::Time dt) = 0;

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
template<typename Derived>
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
