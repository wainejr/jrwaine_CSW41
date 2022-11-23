#include "../defines.h"
#include "SFML/Graphics.hpp"

#ifndef _VIEW_GLOBALS_H_
#define _VIEW_GLOBALS_H_

namespace view {
namespace globals {
    const int RESOLUTION_X = 128;
    const int RESOLUTION_Y = 128;
    const int MAZE_SIZE_X = 28;
    const int MAZE_SIZE_Y = 31;

    const float TILE_SIZE = 4;

    const float SMALL_BALL_SIZE = 1;
    const float BIG_BALL_SIZE = 2;
    const float PACMAN_RADIUS = TILE_SIZE / 2 * 0.9;
    const float GHOST_RADIUS = TILE_SIZE / 2 * 0.9;

    const float MAZE_OFFSET_Y = (int)(RESOLUTION_Y / MAZE_SIZE_Y / 2);
    const float MAZE_OFFSET_X = (int)(RESOLUTION_X / MAZE_SIZE_X / 2);

    void get_normalized_pos(float rel_pos_x, float rel_pos_y, float* abs_pos_x, float* abs_pos_y);
}
}
#endif
