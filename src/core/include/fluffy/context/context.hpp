//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright (c) 2019. All rights reserved.
// File created by loic on 04/05/2019.
//

#pragma once

#include <memory>

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