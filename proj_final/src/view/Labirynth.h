#include "../models/Labyrinth.h"
#include "Base.h"

#ifndef _VIEW_LABYRINTH_H_
#define _VIEW_LABYRINTH_H_

namespace view {

/**
*   @brief View for labyrinth model
*   
*/
class ViewLabyrinth : public Base {

    /**
    *   @brief Draw full labyrinth maze
    *   
    *   @param context context to draw to
    */
    void draw_labyrinth_maze(DrawContext* context);

    /**
    *   @brief Draw a square (tunnel, path or wall) of the maze
    *   
    *   @param context context to draw to
    *   @param pos position of square
    *   @param tl tile in given square
    */
    void draw_maze_square(DrawContext* context, misc::Vector<int> pos, models::TilesTypes tl);

    /**
    *   @brief Draw ball of the maze
    *   
    *   @param context context to draw to
    *   @param pos_ball Ball position in maze
    *   @param is_big True if ball is big, false if not
    */
    void draw_ball(DrawContext* context, misc::Vector<int> pos_ball, bool is_big);

    /**
    *   @brief Update drawing of a tile, drawing black background and then drawing the tile 
    *   
    *   @param context context to draw to
    *   @param tile_pos Position of tile to update
    */
    void update_tile(DrawContext* context, misc::Vector<int> tile_pos);

    /**
    *   @brief Draw tile (including ball or square)
    *   
    *   @param context context to draw to
    *   @param tile_pos position of tile to draw
    *   @param tl tile in given position
    */
    void draw_tile(DrawContext* context, misc::Vector<int> tile_pos, models::TilesTypes tl);

public:
    ViewLabyrinth(models::Labyrinth* lab);

    models::Labyrinth* lab;
    bool maze_drawed;

    /**
    *   @brief Draw labyrinth
    *   
    *   @param context context to draw to
    */
    void draw(DrawContext* context);

    /**
    *   @brief Update tiles drawing near given position
    *   
    *   @param context context to draw to
    *   @param tile_pos central position to update
    */
    void update_near_tiles(DrawContext* context, misc::Vector<int> tile_pos);
};
}
#endif // !_VIEW_LABYRINTH_H_
