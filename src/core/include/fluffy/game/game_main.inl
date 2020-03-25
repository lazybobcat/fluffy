#pragma once

#include <fluffy/definitions.hpp>
#include <fluffy/game/game_loader.hpp>
#include <fluffy/game/game_loop.hpp>
#include <fluffy/game/game_main.hpp>
#include <fluffy/pch.hpp>

using namespace Fluffy;

template<typename T>
int GameMain::main(int argc, char* argv[])
{
    Logger::init(false);

    std::vector<std::string> args;
    for (int i = 0; i < argc; ++i) {
        args.push_back(argv[i]);
    }

    auto context = Context::create();

    try {
        SpecializedGameLoader<T> loader(*context, std::move(args));
        loader.load();
        GameLoop loop(loader);
        loop.run();
        loader.unload();
    } catch (std::exception& e) {
        FLUFFY_LOG_ERROR("Game terminated with an error: " + toString(e.what()));

        return 1;
    } catch (...) {
        FLUFFY_LOG_ERROR("Game terminated with an unexpected error");

        return 1;
    }

    Logger::clear();

    return 0;
}