//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright (c) 2019. All rights reserved.
// File created by loic on 04/05/2019.
//

#include <fluffy/game/game_loader.hpp>

using namespace Fluffy;

GameLoader::GameLoader(ServiceContainer& serviceContainer, std::vector<std::string>&& args)
  : mServiceContainer(serviceContainer)
  , mApplicationArgs(args)
{
}

GameLoader::~GameLoader()
{
    if (mGame) {
        mGame->deInit();
        delete mGame;
    }
}

void GameLoader::load()
{
    unload();

    mGame = createGame();
    mGame->init(mServiceContainer, mApplicationArgs);
}

void GameLoader::reload()
{
    unload();
    load();
}

void GameLoader::unload()
{
    if (mGame) {
        mGame->deInit();
        delete mGame;
    }
}

Game& GameLoader::getGame() const
{
    if (!mGame) {
        throw std::logic_error("The game object is asked to game loader while game is unloaded");
    }

    return *mGame;
}