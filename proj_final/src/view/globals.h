#include "../defines.h"
#include "../models/consts.h"

#ifndef _VIEW_GLOBALS_H_
#define _VIEW_GLOBALS_H_

namespace view {
namespace globals {
    // Goal FPS to achieve
    const float DESIRED_FPS = 10;
    // Screen resolution
    const int RESOLUTION_X = 128;
    const int RESOLUTION_Y = 128;

    // Size of a tile in pixels
    const float TILE_SIZE = 4.0f;

    // Size of objects in pixels
    const float SMALL_BALL_SIZE = 1.0f;
    const float BIG_BALL_SIZE = 2.0f;
    // Size of agents in pixels
    const float PACMAN_RADIUS = 2.0f; // TILE_SIZE / 2.0f * 0.9f;
    const float GHOST_RADIUS = 2.0f; // TILE_SIZE / 2.0f * 0.9f;

    // Consts to help drawing gameplay
    const int MAZE_OFFSET_Y = (RESOLUTION_Y - TILE_SIZE * models::consts::MAZE_SIZE_Y) / 2;
    const int MAZE_OFFSET_X = (RESOLUTION_X - TILE_SIZE * models::consts::MAZE_SIZE_X) / 2;

    /**
    *   @brief Get the normalized position of object
    *   
    *   @param rel_pos_x Relative position to maze in x 
    *   @param rel_pos_y Relative position to maze in y
    *   @param abs_pos_x Absolute position to update in x
    *   @param abs_pos_y Absolute position to update in y
    */
    void get_normalized_pos(float rel_pos_x, float rel_pos_y, float* abs_pos_x, float* abs_pos_y);
}
}
#endif
