#include "../defines.h"
#include "../models/consts.h"

#ifndef _VIEW_GLOBALS_H_
#define _VIEW_GLOBALS_H_

namespace view {
namespace globals {
    const float DESIRED_FPS = 30;
    const int RESOLUTION_X = 128;
    const int RESOLUTION_Y = 128;

    const float TILE_SIZE = 4.0f;

    const float SMALL_BALL_SIZE = 1.0f;
    const float BIG_BALL_SIZE = 2.0f;
    const float PACMAN_RADIUS = TILE_SIZE / 2.0f * 0.9f;
    const float GHOST_RADIUS = TILE_SIZE / 2.0f * 0.9f;

    const int MAZE_OFFSET_Y = (RESOLUTION_Y - TILE_SIZE * models::consts::MAZE_SIZE_Y) / 2;
    const int MAZE_OFFSET_X = (RESOLUTION_X - TILE_SIZE * models::consts::MAZE_SIZE_X) / 2;

    void get_normalized_pos(float rel_pos_x, float rel_pos_y, float* abs_pos_x, float* abs_pos_y);
}
}
#endif
