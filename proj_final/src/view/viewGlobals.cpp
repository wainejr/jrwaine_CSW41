#include "globals.h"

using namespace view;

void globals::get_normalized_pos(float rel_pos_x, float rel_pos_y, float* abs_pos_x, float* abs_pos_y)
{
    float pos_x = MAZE_OFFSET_X + rel_pos_x * TILE_SIZE;
    float pos_y = MAZE_OFFSET_Y + rel_pos_y * TILE_SIZE;
    *abs_pos_x = pos_x;
    *abs_pos_y = pos_y;
};
