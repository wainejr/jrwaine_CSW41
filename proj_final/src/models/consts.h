#include "./../misc/Vector.h"

#ifndef _MODELS_CONSTS_H_
#define _MODELS_CONSTS_H_
namespace models {
enum TilesTypes { WALL,
    TUNNEL,
    PATH,
    SMALL_BALL,
    SUPER_BALL };

namespace consts {

    const TilesTypes W = WALL;
    const TilesTypes s = SMALL_BALL;
    const TilesTypes S = SUPER_BALL;
    const TilesTypes T = TUNNEL;
    const TilesTypes p = PATH;

    const TilesTypes INITIAL_LABYRINTH_STATE[31][28] = {
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

    const float INITIAL_PACMAN_POSITION[2] = { 10, 10 };
    const float INITIAL_GHOST_RED_POSITION[2] = { 10, 10 };
    const float INITIAL_GHOST_YELLOW_POSITION[2] = { 10, 10 };
    const float INITIAL_GHOST_PINK_POSITION[2] = { 10, 10 };
    const float INITIAL_GHOST_BLUE_POSITION[2] = { 10, 10 };

    const float PACMAN_VELOCITY = 0.2;
    const float GHOSTS_VELOCITY = 0.2;

    const float RIGHT[2] = { 1, 0 };
    const float LEFT[2] = { -1, 0 };
    const float UP[2] = { 0, 1 };
    const float DOWN[2] = { 0, -1 };
    const float STOP[2] = { 0, 0 };

    const float INITIAL_PACMAN_DIRECTION[2] = { LEFT[0], LEFT[1] };
    const float INITIAL_GHOST_RED_DIRECTION[2] = { STOP[0], STOP[1] };
    const float INITIAL_GHOST_YELLOW_DIRECTION[2] = { STOP[0], STOP[1] };
    const float INITIAL_GHOST_PINK_DIRECTION[2] = { STOP[0], STOP[1] };
    const float INITIAL_GHOST_BLUE_DIRECTION[2] = { STOP[0], STOP[1] };

} // namespace consts
} // namespace models
#endif