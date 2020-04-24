#include <fluffy/game/game_loader.hpp>

using namespace Fluffy;

GameLoader::GameLoader(std::vector<String>&& args)
  : mApplicationArgs(args)
{
}

GameLoader::~GameLoader()
{
    unload();
}

void GameLoader::load()
{
    ModuleRegistry registry;

    mGame = createGame();

    FLUFFY_LOG_INFO("Starting game {} with Fluffy...", mGame->getTitle());

    mGame->initialize(mApplicationArgs);
    mGame->initializeModules(registry);
    mContext = Unique<Context>(new Context(registry));
    mContext->initialize();
    mGame->setStartingState(mGame->start(), mContext);
}

void GameLoader::reload()
{
    unload();
    load();
}

void GameLoader::unload()
{
    if (!mGame) {
        throw std::logic_error("The game object is asked while still unloaded");
    }

    mGame->terminate(*mContext);
}

Game& GameLoader::getGame() const
{
    if (!mGame) {
        throw std::logic_error("The game object is asked while still unloaded");
    }

    return *mGame;
}