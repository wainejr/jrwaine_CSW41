#include "../models/Labyrinth.h"
#include "Base.h"

#ifndef _VIEW_LABYRINTH_H_
#define _VIEW_LABYRINTH_H_

namespace view {
class ViewLabyrinth : public Base {
    void draw_labyrinth_maze(DrawContext* window);
    void draw_maze_square(DrawContext* window, misc::Vector<int> pos, models::TilesTypes tl);
    void draw_small_ball(DrawContext* window, misc::Vector<int> pos_ball);
    void draw_big_ball(DrawContext* window, misc::Vector<int> pos_ball);

public:
    ViewLabyrinth(models::Labyrinth* lab);

    models::Labyrinth* lab;
    void draw(DrawContext* window);
};
}
#endif // !_VIEW_LABYRINTH_H_
