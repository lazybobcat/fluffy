#pragma once

namespace Fluffy {
class GameMain
{
public:
    template<typename T>
    static int main(int argc, char* argv[]);
};
}

#include <fluffy/game/game_main.inl>

#define FluffyGame(T) \
    int main(int argc, char* argv[]) { return Fluffy::GameMain::main<T>(argc, argv); }
