#include "../models/Labyrinth.h"
#include "Base.h"

#ifndef _VIEW_LABYRINTH_H_
#define _VIEW_LABYRINTH_H_

namespace view {
class ViewLabyrinth : public Base {
    void draw_labyrinth_maze(DrawContext* context);

    void draw_maze_square(DrawContext* context, misc::Vector<int> pos, models::TilesTypes tl);
    void draw_ball(DrawContext* context, misc::Vector<int> pos_ball, bool is_big);
    void update_tile(DrawContext* context, misc::Vector<int> tile_pos);
    void draw_tile(DrawContext* context, misc::Vector<int> tile_pos, models::TilesTypes tl);

public:
    ViewLabyrinth(models::Labyrinth* lab);

    models::Labyrinth* lab;
    bool maze_drawed;
    void draw(DrawContext* context);
    void update_near_tiles(DrawContext* context, misc::Vector<int> tile_pos);
};
}
#endif // !_VIEW_LABYRINTH_H_
