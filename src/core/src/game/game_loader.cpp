//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright (c) 2019. All rights reserved.
// File created by loic on 04/05/2019.
//

#include <fluffy/game/game_loader.hpp>

using namespace Fluffy;

GameLoader::GameLoader(const Context& context, std::vector<std::string>&& args)
  : mContext(context)
  , mApplicationArgs(args)
{
}

GameLoader::~GameLoader()
{
    unload();
}

void GameLoader::load()
{
    unload();

    mGame = createGame();
    mGame->initialize(mContext, mApplicationArgs);
    mGame->setStartingState(mGame->start(), mContext);
}

void GameLoader::reload()
{
    unload();
    load();
}

void GameLoader::unload()
{
}

Game& GameLoader::getGame() const
{
    if (!mGame) {
        throw std::logic_error("The game object is asked while still unloaded");
    }

    return *mGame;
}