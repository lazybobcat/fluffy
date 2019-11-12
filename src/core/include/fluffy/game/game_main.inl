//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright (c) 2019. All rights reserved.
// File created by loic on 04/05/2019.
//

#pragma once

#include <fluffy/game/game_loader.hpp>
#include <fluffy/game/game_loop.hpp>
#include <fluffy/game/game_main.hpp>
#include <fluffy/text/string.hpp>
#include <fluffy/utils/logger.hpp>
#include <memory>
#include <string>
#include <vector>

using namespace Fluffy;

template<typename T>
int GameMain::main(int argc, char* argv[])
{
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
        Logger::getInstance()->log(Logger::LogType::Error, toString("Game terminated with an error: ") + e.what());

        return 1;
    } catch (...) {
        Logger::getInstance()->log(Logger::LogType::Error, "Game terminated with an unexpected error");

        return 1;
    }

    return 0;
}