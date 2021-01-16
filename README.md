[![Generic badge](https://img.shields.io/badge/licence-MIT-brightgreen.svg)](https://en.wikipedia.org/wiki/MIT_License)
[![Build Status](https://travis-ci.org/Lo-X/fluffy.svg?branch=master)](https://travis-ci.org/Lo-X/fluffy)
[![Generic badge](https://img.shields.io/badge/C++-17-brightgreen.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)

Fluffy is still a work in progress.

# Fluffy

Fluffy is a basic video game engine. Its objective is not to be the better and the fastest out there, but simply to
help prototyping games.

Its objective is to highly reduce the amount of code needed to build a game. Of course there will still be some code,
but the goal is to make the user write as little code as possible and instead use scripting and an asset pipe. 

## Fluffy contains

* A fully working Entity-Component-System (ECS)
* Logging
* Window handling
* Graphics handling
* Resource managers
* States (screens/layers)
* Useful utility classes like Time, Signals/slots, Path, etc.
* ImGui windows to help the game development and display useful information

## Fluffy will contain (probably)

* Scripting
* Asset pipe

## Fluffy needs

* A compiler that supports C++17 at least
* OpenGL 3.3+ compatible GPU

## Fluffy uses

* [Bandit/Bandit](https://github.com/banditcpp/) For unit testing
* [open-source-parsers/jsoncpp](https://github.com/open-source-parsers/jsoncpp) For serialization stuff and loading data
* GLAD To bind to OpenGL
* GLFW For window handling
* GLM For graphic maths
* [ImGUI](https://github.com/ocornut/imgui) Because it's awesome
* [STB](http://nothings.org/stb) For image loading
* [FMT](https://fmt.dev/) For text and log formatting
* [scottt/debugbreak](https://github.com/scottt/debugbreak) For breakpoints
* [JustasMasiulis/circular_buffer](https://github.com/JustasMasiulis/circular_buffer) For the useful header-only circular_buffer class

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
    virtual void initialize(EntityManager& entityManager, EventManager& eventManager) override {
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
    systemManager.initialize();
    
    while (/** Game Loop or something **/) {
        systemManager.updateAll(seconds(1 / 60.f));
    }
}
```

### States

