#include "./Labyrinth.h"

using namespace models;

Labyrinth::Labyrinth()
{
    // TUNNEL, PATH, SMALL_BALL, SUPER_BALL
    auto W = TilesTypes::WALL;
    auto p = TilesTypes::PATH;
    auto T = TilesTypes::TUNNEL;
    auto s = TilesTypes::SMALL_BALL;
    auto S = TilesTypes::SUPER_BALL;

    TilesTypes start_lab[31][28] = {
        { W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W },
        { W, s, s, s, s, s, s, s, s, s, s, s, s, W, W, s, s, s, s, s, s, s, s, s, s, s, s, W },
        { W, s, W, W, W, W, s, W, W, W, W, W, s, W, W, s, W, W, W, W, W, s, W, W, W, W, s, W },
        { W, S, W, W, W, W, s, W, W, W, W, W, s, W, W, s, W, W, W, W, W, s, W, W, W, W, S, W },
        { W, s, W, W, W, W, s, W, W, W, W, W, s, W, W, s, W, W, W, W, W, s, W, W, W, W, s, W },
        { W, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, W },
        { W, s, W, W, W, W, s, W, W, s, W, W, W, W, W, W, W, W, s, W, W, s, W, W, W, W, s, W },
        { W, s, W, W, W, W, s, W, W, s, W, W, W, W, W, W, W, W, s, W, W, s, W, W, W, W, s, W },
        { W, s, s, s, s, s, s, W, W, s, s, s, s, W, W, s, s, s, s, W, W, s, s, s, s, s, s, W },
        { W, W, W, W, W, W, s, W, W, W, W, W, p, W, W, p, W, W, W, W, W, s, W, W, W, W, W, W },
        { W, W, W, W, W, W, s, W, W, W, W, W, p, W, W, p, W, W, W, W, W, s, W, W, W, W, W, W },
        { W, W, W, W, W, W, s, W, W, p, p, p, p, p, p, p, p, p, p, W, W, s, W, W, W, W, W, W },
        { W, W, W, W, W, W, s, W, W, p, W, W, W, T, T, W, W, W, p, W, W, s, W, W, W, W, W, W },
        { W, W, W, W, W, W, s, W, W, p, W, p, p, p, p, p, p, W, p, W, W, s, W, W, W, W, W, W },
        { p, p, p, p, p, p, s, p, p, p, W, p, p, p, p, p, p, W, p, p, p, s, p, p, p, p, p, p },
        { W, W, W, W, W, W, s, W, W, p, W, p, p, p, p, p, p, W, p, W, W, s, W, W, W, W, W, W },
        { W, W, W, W, W, W, s, W, W, p, W, W, W, W, W, W, W, W, p, W, W, s, W, W, W, W, W, W },
        { W, W, W, W, W, W, s, W, W, p, p, p, p, p, p, p, p, p, p, W, W, s, W, W, W, W, W, W },
        { W, W, W, W, W, W, s, W, W, p, W, W, W, W, W, W, W, W, p, W, W, s, W, W, W, W, W, W },
        { W, W, W, W, W, W, s, W, W, p, W, W, W, W, W, W, W, W, p, W, W, s, W, W, W, W, W, W },
        { W, s, s, s, s, s, s, s, s, s, s, s, s, W, W, s, s, s, s, s, s, s, s, s, s, s, s, W },
        { W, s, W, W, W, W, s, W, W, W, W, W, s, W, W, s, W, W, W, W, W, s, W, W, W, W, s, W },
        { W, s, W, W, W, W, s, W, W, W, W, W, s, W, W, s, W, W, W, W, W, s, W, W, W, W, s, W },
        { W, S, s, s, W, W, s, s, s, s, s, s, s, p, p, s, s, s, s, s, s, s, W, W, s, s, S, W },
        { W, W, W, s, W, W, s, W, W, s, W, W, W, W, W, W, W, W, s, W, W, s, W, W, s, W, W, W },
        { W, W, W, s, W, W, s, W, W, s, W, W, W, W, W, W, W, W, s, W, W, s, W, W, s, W, W, W },
        { W, s, s, s, s, s, s, W, W, s, s, s, s, W, W, s, s, s, s, W, W, s, s, s, s, s, s, W },
        { W, s, W, W, W, W, W, W, W, W, W, W, s, W, W, s, W, W, W, W, W, W, W, W, W, W, s, W },
        { W, s, W, W, W, W, W, W, W, W, W, W, s, W, W, s, W, W, W, W, W, W, W, W, W, W, s, W },
        { W, s, s, s, s, s, s, s, s, s, s, s, s, W, W, s, s, s, s, s, s, s, s, s, s, s, s, W },
        { W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W },
    };

    for (int j = 0; j < 31) {
        for (int i = 0; i < 28; i++) {
            this->lab[j][i] = start_lab[j][i];
        }
    }
}
