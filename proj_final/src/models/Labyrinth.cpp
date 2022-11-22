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

    for (int j = 0; j < 31) {
        for (int i = 0; i < 28; i++) {
            this->lab[j][i] = INITIAL_LABYRINTH_STATE[j][i];
        }
    }
}
