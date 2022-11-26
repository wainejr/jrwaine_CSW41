#include "./Labyrinth.h"

using namespace models;

Labyrinth::Labyrinth()
{
    this->n_balls = 0;
    for (int j = 0; j < consts::MAZE_SIZE_Y; j++) {
        for (int i = 0; i < consts::MAZE_SIZE_X; i++) {
            TilesTypes tl = consts::INITIAL_LABYRINTH_STATE[j][i];
            this->lab[j][i] = tl;
            if (tl == TilesTypes::SMALL_BALL || tl == TilesTypes::SUPER_BALL) {
                n_balls += 1;
            }
        }
    }
}

TilesTypes Labyrinth::get_tile(int x, int y)
{
    int x_val = misc::remainder(x, consts::MAZE_SIZE_X);
    int y_val = misc::remainder(y, consts::MAZE_SIZE_Y);
    return this->lab[y_val][x_val];
}

void Labyrinth::consume_tile(int x, int y)
{
    TilesTypes tl = this->get_tile(x, y);
    if (tl == TilesTypes::SMALL_BALL || tl == TilesTypes::SUPER_BALL) {
        this->lab[y][x] = TilesTypes::PATH;
        n_balls -= 1;
    }
}

bool Labyrinth::is_incave(int x, int y)
{
    if (x > 10 && x < 17) {
        if (y > 12 && y < 16) {
            return true;
        }
    }
    if (y == 12 && (x == 13 || x == 14)) {
        return true;
    }
    return false;
}
