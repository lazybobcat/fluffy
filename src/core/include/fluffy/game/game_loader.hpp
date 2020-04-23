#pragma once

#include <fluffy/game/game.hpp>
#include <fluffy/pch.hpp>

namespace Fluffy {
class GameLoader
{
public:
    explicit GameLoader(std::vector<String>&& args);
    virtual ~GameLoader();

    void load();
    void unload();
    void reload();

    Game& getGame() const;

protected:
    virtual std::unique_ptr<Game> createGame() { return nullptr; }

private:
    std::unique_ptr<Context> mContext;
    std::vector<String>      mApplicationArgs;

    std::unique_ptr<Game> mGame = nullptr;
};

template<typename T>
class SpecializedGameLoader final : public GameLoader
{
public:
    explicit SpecializedGameLoader(std::vector<String>&& args)
      : GameLoader(std::move(args))
    {}

protected:
    std::unique_ptr<Game> createGame() override { return std::make_unique<T>(); }
};
}