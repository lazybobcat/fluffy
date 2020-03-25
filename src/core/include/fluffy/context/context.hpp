#pragma once

#include <fluffy/pch.hpp>

namespace Fluffy {

class GameMain;

class Context
{
public:
    ~Context();

    // @todo raw pointers below :
    // graphics
    // audio
    // resources
    // network
    // system
    // ...

private:
    friend class GameMain;

    void initialize();
    void terminate();

    static std::unique_ptr<Context> create();

private:
    // @todo unique_ptr below :
    // graphics
    // audio
    // resources
    // network
    // system
    // ...
};
}