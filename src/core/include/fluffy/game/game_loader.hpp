#pragma once

#include <fluffy/game/game.hpp>
#include <fluffy/pch.hpp>

namespace Fluffy {
class GameLoader
{
public:
    GameLoader(const Context& context, std::vector<std::string>&& args);
    virtual ~GameLoader();

    void load();
    void unload();
    void reload();

    Game& getGame() const;

protected:
    virtual std::unique_ptr<Game> createGame() { return nullptr; }

private:
    const Context&           mContext;
    std::vector<std::string> mApplicationArgs;

    std::unique_ptr<Game> mGame = nullptr;
};

template<typename T>
class SpecializedGameLoader final : public GameLoader
{
public:
    SpecializedGameLoader(const Context& context, std::vector<std::string>&& args)
      : GameLoader(context, std::move(args))
    {}

protected:
    std::unique_ptr<Game> createGame() override { return std::make_unique<T>(); }
};
}