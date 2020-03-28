#pragma once

#include <fluffy/api/modules.hpp>
#include <fluffy/pch.hpp>

namespace Fluffy {

class GameMain;
class GameLoader;

class Context
{
public:
    ~Context();

    // @todo getters below :
    SystemModule* system = nullptr;
    VideoModule*  video  = nullptr;
    // graphics
    // audio
    // resources
    // network
    // ...

private:
    friend class GameMain;
    friend class GameLoader;

    void assign();
    void initialize();
    void terminate();

    explicit Context(const ModuleRegistry& registry);

private:
    // @todo unique_ptr below :
    std::unique_ptr<SystemModule> systemModule;
    std::unique_ptr<VideoModule>  videoModule;
    // audio
    // resources
    // network
    // ...
};
}