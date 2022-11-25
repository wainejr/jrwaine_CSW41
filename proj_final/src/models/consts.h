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

    const int MAZE_SIZE_X = 28;
    const int MAZE_SIZE_Y = 31;

    const TilesTypes INITIAL_LABYRINTH_STATE[MAZE_SIZE_Y][MAZE_SIZE_X] = {
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

    // Update state every 20 ms,
    const float STATE_UPDATE_SEC_INTERVAL = 0.020f;

    const int SMALL_BALL_SCORE = 10;
    const int SUPER_BALL_SCORE = 50;
    const int GHOST_AFRAID_SCORE = 200;
    const float SCORE_MUL_DECREASE_PER_SEC = 0.05f;
    const float SCORE_MIN_MUL = 0.1f;
    const float SCORE_MUL_DECREASE_PER_UPDATE = SCORE_MUL_DECREASE_PER_SEC * STATE_UPDATE_SEC_INTERVAL;

    const float TIME_SEC_SUPER_PACMAN = 10;
    const int N_UPDATES_SUPER_PACMAN = (int)(TIME_SEC_SUPER_PACMAN / STATE_UPDATE_SEC_INTERVAL);

    // 0 is top and 31 is down
    // 0 is left and 27 is right
    // Position is in top-left of tile
    const float INITIAL_PACMAN_POSITION[2] = { 13.5f, 23.0f };
    const float INITIAL_GHOST_RED_POSITION[2] = { 13.5f, 11.0f };
    const float INITIAL_GHOST_YELLOW_POSITION[2] = { 15.5f, 14.0f };
    const float INITIAL_GHOST_PINK_POSITION[2] = { 11.5f, 14.0f };
    const float INITIAL_GHOST_BLUE_POSITION[2] = { 13.5f, 14.0f };

    const int GHOST_RESET_INCAVE_POSITION[2] = {13, 14};

    const float DESIRED_FPS = 30;

    // 0.6 seconds to pass a tile for each second
    const float PACMAN_VELOCITY_PER_SEC = 6.0f;
    const float GHOSTS_VELOCITY_PER_SEC = 1.2f;

    const float RIGHT[2] = { 1.0f, 0.0f };
    const float LEFT[2] = { -1.0f, 0.0f };
    // Y axis is invertex actually
    const float UP[2] = { 0.0f, -1.0f };
    const float DOWN[2] = { 0.0f, 1.0f };
    const float STOP[2] = { 0.0f, 0.0f };

    const float INITIAL_PACMAN_DIRECTION[2] = { LEFT[0], LEFT[1] };
    const float INITIAL_GHOST_RED_DIRECTION[2] = { STOP[0], STOP[1] };
    const float INITIAL_GHOST_YELLOW_DIRECTION[2] = { STOP[0], STOP[1] };
    const float INITIAL_GHOST_PINK_DIRECTION[2] = { STOP[0], STOP[1] };
    const float INITIAL_GHOST_BLUE_DIRECTION[2] = { STOP[0], STOP[1] };

} // namespace consts
} // namespace models
#endif