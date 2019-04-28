//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 27/04/18.
//

#include <bandit/bandit.h>
#include <fluffy/fluffy_ecs.hpp>

using namespace bandit;
using namespace snowhouse;

std::ostream& operator<<(std::ostream& os, const Entity &e)
{
    os << "Entity#" << e.id().index() << "/" << e.id().version();

    return os;
}

struct Position : public Component<Position>
{
    Position() = default;
    Position(float x, float y) : x(x), y(y) {}

    float x = 0.f;
    float y = 0.f;
};

struct Speed : public Component<Speed>
{
    Speed() = default;
    Speed(float x, float y) : x(x), y(y) {}

    float x = 0.f;
    float y = 0.f;
};

go_bandit([](){
    describe("ECS", [&](){
        EventManager eventManager;
        EntityManager entityManager(eventManager);

        describe("EntityManager", [&]() {
            it("should give entities correct indexes and versions", [&]() {
                Entity entity1 = entityManager.createEntity();
                Entity entity2 = entityManager.createEntity();

                AssertThat(entity1.isValid(), Equals(true));
                AssertThat(entity2.isValid(), Equals(true));

                AssertThat(entity1.id().index(), Equals(static_cast<unsigned int>(0)));
                AssertThat(entity1.id().version(), Equals(static_cast<unsigned int>(1)));
                AssertThat(entity2.id().index(), Equals(static_cast<unsigned int>(1)));
                AssertThat(entity2.id().version(), Equals(static_cast<unsigned int>(1)));

                entity1.destroy();
                Entity entity3 = entityManager.createEntity();
                AssertThat(entity1.isValid(), Equals(false));
                AssertThat(entity3.isValid(), Equals(true));
                AssertThat(entity3.id().index(), Equals(static_cast<unsigned int>(0)));
                AssertThat(entity3.id().version(), Equals(static_cast<unsigned int>(2)));
            });

            it("should be able to find Entities", [&]() {
                Entity entity1 = entityManager.createEntity();
                Entity entity2 = entityManager.getEntity(entity1.id());

                AssertThat(entity1.id(), Equals(entity2.id()));
            });

            it("should be properly reseted", [&]() {
                entityManager.reset();
                Entity entity1 = entityManager.createEntity();

                AssertThat(entity1.id().index(), Equals(static_cast<unsigned int>(0)));
                AssertThat(entity1.id().version(), Equals(static_cast<unsigned int>(1)));
            });
        });

        describe("Component", [&]() {
            before_each([&]() {
                entityManager.reset();
            });

            it("should be attached to entities", [&]() {
                Entity entity1 = entityManager.createEntity();
                entity1.assign<Position>();
                entity1.assign<Speed>();

                AssertThat(entity1.hasComponent<Speed>(), Equals(true));
                AssertThat(entity1.hasComponent<Position>(), Equals(true));
            });

            // @todo test component data persistence
        });

        describe("EntityComponentView", [&]() {
            before_each([&]() {
                entityManager.reset();
            });

            it("should contain Component holding Entities", [&]() {
                {
                    auto view = entityManager.each<Position>();
                    AssertThat(view.size(), Equals(static_cast<unsigned int>(0)));
                }

                Entity entity1 = entityManager.createEntity();
                entity1.assign<Position>();

                {
                    auto view = entityManager.each<Position>();
                    AssertThat(view.size(), Equals(static_cast<unsigned int>(1)));
                }

                Entity entity2 = entityManager.createEntity();
                entity2.assign<Position>();

                {
                    auto view = entityManager.each<Position>();
                    AssertThat(view.size(), Equals(static_cast<unsigned int>(2)));
                }
            });

            it("should allow iteration", [&]() {
                Entity entity1 = entityManager.createEntity();
                entity1.assign<Position>();

                Entity entity2 = entityManager.createEntity();
                entity2.assign<Position>();

                std::size_t count = 0;
                for (auto entity : entityManager.each<Position>()) {
                    if (entity.isValid()) {}
                    ++count;
                }

                AssertThat(count, Equals(static_cast<unsigned int>(2)));
            });

            it("should not allow iteration when empty", [&]() {
                std::size_t count = 0;
                for (auto entity : entityManager.each<Position>()) {
                    if (entity.isValid()) {}
                    ++count;
                }

                AssertThat(count, Equals(static_cast<unsigned int>(0)));
            });
        });

        // @todo test systems
    });
});