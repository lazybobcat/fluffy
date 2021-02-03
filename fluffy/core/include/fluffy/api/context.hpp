#pragma once

#include <fluffy/api/modules.hpp>
#include <fluffy/definitions.hpp>
#include <fluffy/event/event_manager.hpp>
#include <fluffy/pch.hpp>

namespace Fluffy {

class GameMain;
class GameLoader;

class Context
{
public:
    ~Context();

    EventManager* events = nullptr;

    // @todo getters below :
    SystemModule*   system   = nullptr;
    VideoModule*    video    = nullptr;
    InputModule*    input    = nullptr;
    SoftwareModule* software = nullptr;
    // audio
    // resources
    // network
    // ...

#ifdef FLUFFY_UNIT_TESTING
    Context() = default;
#endif

private:
    friend class GameMain;
    friend class GameLoader;

    void assign();
    void initialize();
    void terminate();

    explicit Context(const ModuleRegistry& registry);

private:
    Unique<EventManager> eventManager;

    // @todo unique_ptr below :
    Unique<SystemModule>   systemModule;
    Unique<VideoModule>    videoModule;
    Unique<InputModule>    inputModule;
    Unique<SoftwareModule> softwareModule;
    // audio
    // resources
    // network
    // ...
};
}