[![Build Status](https://travis-ci.org/Lo-X/fluffy.svg?branch=master)](https://travis-ci.org/Lo-X/fluffy)

Fluffy is still a work in progress.

# Fluffy

Fluffy is a 2D video game basic framework. Its objective is not to be the better and the fastest out there, but simply to
help prototyping games.

Fluffy  will offer a bunch of utility tools, a service container, time and clock, an ECS, game states, an event system, 
scripting, asset pipes, and whatever comes to my mind or yours.

__Please mind that Fluffy currently has a dependency on Selene (Lua) but that this is subject to change soon!__

Even if I'm planning to use it mainly with [SFML](https://github.com/SFML/SFML), I don't want Fluffy to be tied to it 
so that anyone can use it with whatever multimedia/graphic lib he wants. So that means there will be no window handling, 
no GUI, keyboard and mouse nor drawing included directly in Fluffy. But I plan on making a plugin to bridge Fluffy and
SFML.

## Fluffy needs

* A compiler that supports C++14 at least
* SFML 2.x

## Fluffy uses

* [Bandit/Bandit](https://github.com/banditcpp/) For unit testing
* [open-source-parsers/jsoncpp](https://github.com/open-source-parsers/jsoncpp) For serialization stuff and loading data
* [sfml/sfml](https://github.com/sfml/sfml) SFML for graphic/math helpers and multimedia

## How to compile

Use  `cmake` and the compiler of your choice

## Some code examples while waiting a documentation and the wiki

### ECS

Entities are just identifiers. Components hold the actual data (but no functionality). Entity creation and 
assignment of Components:
```
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
 
{
    EntityManager em(eventManager);
    
    // Create the entity
    Entity entity1 = em.createEntity();
    
    // You can assign and initialize a component using the EntityManager
    em.assign<Position>(entity1.id(), 42.f, 30.f);
    
    // Or you can assign a component directly from the Entity
    entity1.assign<Speed>(10, 15);
}
```

Get back components from an Entity:
```
{
    // You can fetch it from the EntityManager...
    auto position = em.component<Position>(entity1.id());
    
    // ... or directly from the Entity
    auto speed = entity1.component<Speed>();
 
    std::cout << "Ent1 position is (" << position->x << ":" << position->y << ") with a speed of (" << speed->x << ":" << speed->y << ")" << std::endl;
}
```

Looping on a list of components:
```
{
    for (auto entity : entityManager.each<Speed, Position>()) {
        auto position = entity.component<Position>();
        auto speed = entity.component<Speed>();
        // ...
    }
}
```

System are responsible for the update ad handling of the dat stored in Components. Creating Systems:
```
class MovementSystem : public System<MovementSystem>
{
public:
    virtual void configure(EntityManager& entityManager, EventManager& eventManager) override {
        // ...
    }
 
    virtual void update(EntityManager& entityManager, Time dt) override {
        for (auto entity : entityManager.each<Speed, Position>()) {
            auto position = entity.component<Position>();
            auto speed = entity.component<Speed>();
            position->x += speed->x * dt.seconds();
            position->y += speed->y * dt.seconds();
        }
    }
};
 
{
    SystemManager systemManager(em, eventManager);
 
    auto movementSystem = systemManager.add<MovementSystem>();
    systemManager.configure();
    
    while (/** Game Loop or something **/) {
        systemManager.updateAll(seconds(1 / 60.f));
    }
}
```

### States

Create and add a State to the StateStack:
```
class TitleState : public State<TitleState>
{
public:
    void initialize(ServiceContainer& serviceContainer) override
    {
        BaseState::initialize(serviceContainer);

        if (serviceContainer.has<EventManager>()) {
            _tickSlot = serviceContainer.get<EventManager>()->connect<GameTickEvent>(std::bind(&TitleState::onGameTickEvent, this, std::placeholders::_1));
        }
    }
 
    void terminate() override
    {
        BaseState::terminate();

        _tickSlot.disconnect();
    }
 
    void onGameTickEvent(const GameTickEvent& event)
    {
        std::cout << "TICK!!!" << std::endl;
    }
 
    Slot _tickSlot;
};
 
{
    StateStack stack(serviceContainer);
    stack.registerState<TitleState>();
    stack.push<TitleState>();
 
    while (/** Game Loop or something**/) {
        BeforeGameTickEvent beforeGameTickEvent;
        serviceContainer.get<EventManager>()->emit(beforeGameTickEvent);
        
        GameTickEvent gameTickEvent(seconds(1/60.f));
        serviceContainer.get<EventManager>()->emit(gameTickEvent);
        
        AfterGameTickEvent afterGameTickEvent;
        serviceContainer.get<EventManager>()->emit(afterGameTickEvent);
    }
}
```

The StateStack apply the pending changes (push state, pop state or clear states) when BeforeGameTickEvent and 
AfterGameTickEvent are raised.

Here, the TitleState class also define a callback to be called when GameTickEvent is raised.
