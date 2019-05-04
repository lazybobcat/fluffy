//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright (c) 2019. All rights reserved.
// File created by loic on 04/05/2019.
//

#pragma once

#include <fluffy/game/game.hpp>
#include <memory>

namespace Fluffy {
class GameLoader
{
public:
    GameLoader(ServiceContainer& serviceContainer, std::vector<std::string>&& args);
    virtual ~GameLoader();

    void load();
    void unload();
    void reload();

    Game& getGame() const;

protected:
    virtual Game* createGame() { return nullptr; }

private:
    ServiceContainer&        mServiceContainer;
    std::vector<std::string> mApplicationArgs;

    Game* mGame = nullptr;
};

template<typename T>
class SpecializedGameLoader final : public GameLoader
{
public:
    SpecializedGameLoader(ServiceContainer& serviceContainer, std::vector<std::string>&& args)
      : GameLoader(serviceContainer, std::move(args))
    {}

protected:
    Game* createGame() override { return new T(); }
};
}