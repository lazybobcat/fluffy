#pragma once

#include <fluffy/definitions.hpp>
#include <fluffy/game/game_loader.hpp>
#include <fluffy/game/game_loop.hpp>
#include <fluffy/game/game_main.hpp>
#include <fluffy/pch.hpp>
#include <fluffy/profiling/profiler.hpp>

using namespace Fluffy;

template<typename T>
int GameMain::main(int argc, char* argv[])
{
    Logger::init(false);
    FLUFFY_PROFILE_START_SESSION(ScopeProfiler::SessionType::MainThread);

    std::vector<String> args;
    for (int i = 0; i < argc; ++i) {
        args.push_back(argv[i]);
    }

    try {
        SpecializedGameLoader<T> loader(std::move(args));
        loader.load();
        GameLoop loop(loader);
        loop.run();
        loader.unload();
    } catch (std::exception& e) {
        FLUFFY_LOG_ERROR("Game terminated with an error: {}", e.what());

        return 1;
    } catch (...) {
        FLUFFY_LOG_ERROR("Game terminated with an unexpected error");

        return 1;
    }

    FLUFFY_PROFILE_END_SESSION(ScopeProfiler::SessionType::MainThread);
    Logger::clear();

    return 0;
}